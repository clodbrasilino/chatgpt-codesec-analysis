"""Plain-language reports from completed audit records; no experiment reads."""
from collections import Counter
from datetime import datetime


def number(value):
    return f"{int(value):,}".replace(",", ".")


def render_health_report(summaries, comparisons, anomalies, metadata, *, short=False):
    total = lambda key: sum(row.get(key) or 0 for row in summaries)
    issues = Counter(row["check"] for row in anomalies)
    manifests = sum(bool(row["manifest_present"]) for row in summaries)
    missing_cells = len({(row["model"], row["cell"]) for row in comparisons if row["comparison"] == "missing_cell"})
    date = datetime.fromisoformat(metadata["started_at"]).strftime("%d/%m/%Y")
    n = number
    lines = [
        "# Conferência dos dados", "",
        f"Dados conferidos em {date}: **{len(summaries)} configurações**, **{n(total('n_generated'))} códigos iniciais** e **{n(total('source_versions'))} versões** ao longo das rodadas.", "",
        "A conferência usa os arquivos locais do projeto. **Não foi feita uma comparação dos commits do Clodoaldo por ano.**", "",
        "| Pedido | Resultado |", "|---|---|",
        f"| Gerou tudo? | Nas {manifests} configurações com manifest, faltam **{n(total('generation_missing'))} códigos** e há **{n(total('generation_extra'))} extras**. Nas {len(summaries)-manifests} sem manifest, não dá para confirmar. |",
        f"| A fila de cura confere? | **{n(total('routing_extra'))} entradas a mais** e **{n(total('routing_missing'))} faltas comprovadas** na comparação com os relatórios salvos. Há **{n(issues['heal_result_unavailable'])} entradas sem resultado salvo**. |",
        f"| Os comentários conferem? | **{n(total('annotations_match'))} de {n(total('annotations_checked'))}** conferem; **{n(total('annotations_mismatch'))} diferem**. Mudanças no código fora dos comentários: **{n(total('source_code_changed'))}**. |",
        f"| Os resultados das rodadas conferem? | **{n(total('outcome_mismatches'))} diferenças** na contagem dos manifests. Isso não confirma que os testes foram interpretados corretamente. |",
        f"| A planilha está completa? | Tem **{len(summaries)-missing_cells} das {len(summaries)} configurações**; faltam **{missing_cells}**. Compilação sem arquivos `.o` fica não verificável. |", "",
        "**Prioridade:** revisar a leitura dos testes e do Flawfinder antes de usar as taxas no artigo. Depois, recuperar os arquivos que faltam e conferir as versões dos comentários.", "",
    ]
    cases = [
        ("test_without_verdict", "Teste sem dizer se passou ou falhou", "Não contar como aprovado; informar quantos testes têm veredito."),
        ("flawfinder_unconsumed", "Relatórios do Flawfinder com alertas ignorados", "Corrigir a leitura dos alertas. Alerta não é defeito confirmado."),
        ("annotation_mismatch", "Comentário e relatório diferentes", "Comparar as versões e conferir se houve retomada."),
        ("missing_source", "Código esperado que falta", "Recuperar os arquivos previstos no manifest."),
        ("tool_execution_error", "Erro ao rodar a ferramenta", "Conferir o erro antes de considerar o resultado válido."),
        ("foreign_diagnostic_location", "Alerta ligado a outro arquivo", "Conferir o arquivo citado no relatório."),
        ("finding_line_out_of_range", "Número de linha fora do código", "Conferir a origem do alerta e a versão do código."),
        ("missing_report", "Relatório obrigatório que falta", "Recuperar o relatório exigido pela configuração."),
        ("missing_manifest", "Manifest que falta", "Recuperar a configuração e o registro da execução."),
        ("report_coverage_gap", "Possível relatório faltando", "Conferir a configuração; a falta ainda não está comprovada."),
        ("heal_result_unavailable", "Cura sem resultado salvo", "Conferir se a rodada terminou e se os arquivos foram copiados."),
        ("recorded_heal_failure", "Falha de cura registrada", "Conferir a falha indicada no manifest."),
    ]
    lines += ["## Principais problemas", "", "| Problema | Quantidade | Próximo passo |", "|---|---:|---|"]
    for check, title, action in cases:
        if issues[check] and (not short or check in {"test_without_verdict", "flawfinder_unconsumed", "annotation_mismatch", "missing_source", "tool_execution_error"}):
            lines.append(f"| {title} | {n(issues[check])} | {action} |")
    lines += ["", "As quantidades acima contam ocorrências ao longo das rodadas. Um arquivo pode aparecer em mais de um problema; não some tudo como se fossem arquivos diferentes.", ""]
    if short:
        lines += ["Os exemplos com caminhos relativos e o método estão em `report.md`. Todos os casos estão em `anomalies.csv`.", "",
                  "São dois arquivos: `by_configuration.xlsx` e `model_comparison.xlsx`. Os valores recalculados, os registrados e as diferenças ficam em abas separadas. Recalcular é conferir os valores pelos arquivos; não significa que todos os valores anteriores estavam errados.", ""]
        return "\n".join(lines)

    tests = Counter()
    for row in summaries:
        tests.update(row["test_states_initial"])
    tested = tests["passed"] + tests["failed"]
    lines += [f"Na rodada inicial, **{n(total('initial_flawfinder_only_files'))} códigos** têm alertas do Flawfinder e nenhum alerta positivo lido nos demais relatórios.", "",
              "## O que os testes dizem", "", "| Resultado na rodada inicial | Arquivos |", "|---|---:|"]
    for state, label in [("passed", "Passou"), ("failed", "Falhou"), ("cli_exercised", "Só executou pela CLI"), ("compile_error", "Não compilou para o teste"), ("no_interface", "Sem interface para testar"), ("absent", "Sem relatório de teste"), ("empty", "Relatório vazio"), ("unknown", "Resultado não reconhecido"), ("no_spec", "Sem especificação de teste")]:
        if tests[state]:
            lines.append(f"| {label} | {n(tests[state])} |")
    lines += ["", f"**{n(tests['passed'])} de {n(tested)}** arquivos com veredito passaram. Só **{n(tested)} de {n(total('n_generated'))}** códigos iniciais têm esse veredito. São duas bases diferentes: aprovação e cobertura.", "",
              "O pipeline pode contar simples execução pela CLI, erro de compilação ou falta de interface como aprovação. Esses casos não comprovam que o código passou no teste.", ""]
    lines += ["## Exemplos para conferir", "", "Caminhos a partir da raiz `chatgpt-codesec-analysis/`. Para arquivos que faltam, o caminho indica onde deveriam estar.", "", "| Caso | Caminho relativo |", "|---|---|"]
    labels = dict((check, title) for check, title, _ in cases)
    for check in ["missing_source", "test_without_verdict", "flawfinder_unconsumed", "annotation_mismatch", "tool_execution_error", "foreign_diagnostic_location", "missing_report"]:
        row = next((row for row in anomalies if row["check"] == check), None)
        if row:
            lines.append(f"| {labels[check]} | `{row['relative_path']}` |")
    missing = [row["basename"] + ".c" for row in anomalies if row["check"] == "missing_source"]
    extras = [row["basename"] + ".c" for row in anomalies if row["check"] == "unexpected_generation"]
    if missing and len(missing) <= 10:
        lines += ["", "Códigos ausentes: " + ", ".join(f"`{name}`" for name in missing) + "."]
    if extras and len(extras) <= 10:
        lines += ["", "Códigos extras: " + ", ".join(f"`{name}`" for name in extras) + "."]
    tool_errors = [row for row in anomalies if row["check"] == "tool_execution_error"]
    if any("unable to remove file: Operation not permitted" in row["evidence"] for row in tool_errors):
        lines += ["", "No Clang, a mensagem observada foi `unable to remove file: Operation not permitted`. Ela indica um erro da ferramenta, mas não prova que toda a análise falhou."]
    lines += ["", "## Como o pipeline se comporta", "",
              "| Ponto | Funcionamento observado |", "|---|---|",
              "| Comentário de teste | Fica acima da função usada no teste, muitas vezes perto do início. Não é um cabeçalho fixo. |",
              "| Medição e feedback | `measure` define os relatórios esperados. `feedback` define os comentários e a fila de cura. |",
              "| Retomada | Pode trocar relatórios dinâmicos e manter comentários antigos. É uma causa possível para diferenças, ainda não comprovada em cada caso. |",
              "| Flawfinder | O parser atual pode ignorar o formato dos alertas. Reproduzir o parser não confirma que os dados estão corretos. |",
              "| Última rodada | Pode deixar uma fila adicional. Isso, sozinho, não significa que faltou executar outra cura. |", "",
              "Esses são os pontos em que a execução difere da descrição do fluxo.", "",
              "## Como ler a planilha", "",
              "`by_configuration.xlsx` tem uma linha por modelo e configuração. `model_comparison.xlsx` coloca os modelos lado a lado e permite escolher a configuração. Cada arquivo funciona sozinho.", "",
              "Os valores recalculados, os registrados e as diferenças ficam em abas separadas. Recalcular é conferir os valores pelos arquivos; não significa que todos os valores anteriores estavam errados.", "",
              "**NV** significa não verificável; **Sem registro**, valor ausente da planilha original; **Sem célula**, modelo sem aquela configuração; **N/A**, não se aplica. Ausência de evidência não vira zero.", "",
              "As contagens de alertas representam arquivos sinalizados pelo pipeline, não vulnerabilidades confirmadas. As taxas de “limpeza” seguem essa mesma regra. Diferença é recalculado menos registrado; para taxas, a planilha usa pontos percentuais.", "",
              "Tarefas e amostras podem variar mesmo com nomes de configuração parecidos. Confira o total gerado e o contexto antes de comparar modelos.", "",
              "## Como a checagem foi feita", "",
              "Os manifests definem tarefas, amostras e rodadas esperadas. Sem eles, a checagem aponta apenas problemas observáveis. ASan e fuzz podem produzir relatórios só em parte dos arquivos; a ausência isolada não comprova erro.", "",
              "Os comentários foram gerados em memória e comparados com os salvos. A comparação aceita mudança na ordem das mensagens e espaços finais dentro dos comentários. Mudança no código, comentário deslocado, mensagem vazia e linha inválida são checados à parte.", "",
              "Relatório vazio não prova sucesso. Compilação sem `.o` e resultados finais sem manifest ficam não verificáveis. Dados, pipeline e planilha original foram preservados; não houve nova chamada aos modelos nem execução dos experimentos.", "",
              ("O inventário dos arquivos de entrada e o hash da planilha original permaneceram iguais durante a checagem." if metadata["input_stability"] == "unchanged" else "Os arquivos de entrada mudaram durante a checagem; confira run.json antes de usar os resultados."), "",
              "Código consultado: `src/pipeline/comment_inject.py`, `src/dyn/runner.py`, `src/pipeline/run_experiment.py`, `src/analysis/metrics.py` e `docs/architecture.md`.", "",
              "## Arquivos gerados", "", "| Arquivo | Uso |", "|---|---|",
              "| `summary.md` | Leitura rápida dos resultados. |",
              "| `summary.csv` | Uma linha por configuração. |",
              "| `anomalies.csv` | Todos os casos, com caminhos relativos, evidências e ações. |",
              "| `metrics_comparison.csv` | Registrado, recalculado, diferença e motivo. |",
              "| `by_configuration.xlsx` | Uma linha por modelo e configuração. |",
              "| `model_comparison.xlsx` | Modelos lado a lado para a configuração escolhida. |",
              "| `cells/` | Detalhes por arquivo e rodada. |",
              "| `run.json` e `validation.json` | Registro da execução e das verificações. |", "",
              "## Repetir a checagem", "", "Na pasta do projeto:", "", "```sh",
              ".venv/bin/python -m src.analysis.health_check --all --output-dir reports/code-health",
              "```", "",
              "Para selecionar um modelo, troque `--all` por `--model NOME`; acrescente `--cell CONFIGURAÇÃO` para uma única configuração. A checagem recalcula a seleção e só substitui cada arquivo de saída depois de terminar de gravá-lo.", "",
              "O destino não pode ser uma pasta de dados, código ou resultados originais. Código de saída 0: checagem concluída, mesmo com problemas nos dados. Código 2: erro ao executar ou mudança nas entradas.", ""]
    return "\n".join(lines)
