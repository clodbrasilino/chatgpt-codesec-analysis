# Conferência dos dados

Dados conferidos em 14/09/2026: **30 configurações**, **21.513 códigos iniciais** e **38.984 versões** ao longo das rodadas.

A conferência usa os arquivos locais do projeto. **Não foi feita uma comparação dos commits do Clodoaldo por ano.**

| Pedido | Resultado |
|---|---|
| Gerou tudo? | Nas 21 configurações com manifest, faltam **4 códigos** e há **2 extras**. Nas 9 sem manifest, não dá para confirmar. |
| A fila de cura confere? | **5 entradas a mais** e **0 faltas comprovadas** na comparação com os relatórios salvos. Há **272 entradas sem resultado salvo**. |
| Os comentários conferem? | **18.382 de 18.439** conferem; **57 diferem**. Mudanças no código fora dos comentários: **0**. |
| Os resultados das rodadas conferem? | **0 diferenças** na contagem dos manifests. Isso não confirma que os testes foram interpretados corretamente. |
| A planilha está completa? | Tem **8 das 30 configurações**; faltam **22**. Compilação sem arquivos `.o` fica não verificável. |

**Prioridade:** revisar a leitura dos testes e do Flawfinder antes de usar as taxas no artigo. Depois, recuperar os arquivos que faltam e conferir as versões dos comentários.

## Principais problemas

| Problema | Quantidade | Próximo passo |
|---|---:|---|
| Teste sem dizer se passou ou falhou | 11.082 | Não contar como aprovado; informar quantos testes têm veredito. |
| Relatórios do Flawfinder com alertas ignorados | 12.805 | Corrigir a leitura dos alertas. Alerta não é defeito confirmado. |
| Comentário e relatório diferentes | 57 | Comparar as versões e conferir se houve retomada. |
| Código esperado que falta | 4 | Recuperar os arquivos previstos no manifest. |
| Erro ao rodar a ferramenta | 103 | Conferir o erro antes de considerar o resultado válido. |
| Alerta ligado a outro arquivo | 509 | Conferir o arquivo citado no relatório. |
| Número de linha fora do código | 491 | Conferir a origem do alerta e a versão do código. |
| Relatório obrigatório que falta | 68 | Recuperar o relatório exigido pela configuração. |
| Manifest que falta | 9 | Recuperar a configuração e o registro da execução. |
| Possível relatório faltando | 200 | Conferir a configuração; a falta ainda não está comprovada. |
| Cura sem resultado salvo | 272 | Conferir se a rodada terminou e se os arquivos foram copiados. |
| Falha de cura registrada | 2 | Conferir a falha indicada no manifest. |

As quantidades acima contam ocorrências ao longo das rodadas. Um arquivo pode aparecer em mais de um problema; não some tudo como se fossem arquivos diferentes.

Na rodada inicial, **3.708 códigos** têm alertas do Flawfinder e nenhum alerta positivo lido nos demais relatórios.

## O que os testes dizem

| Resultado na rodada inicial | Arquivos |
|---|---:|
| Passou | 411 |
| Falhou | 513 |
| Só executou pela CLI | 3.574 |
| Não compilou para o teste | 1.195 |
| Sem interface para testar | 2.501 |
| Sem relatório de teste | 13.319 |

**411 de 924** arquivos com veredito passaram. Só **924 de 21.513** códigos iniciais têm esse veredito. São duas bases diferentes: aprovação e cobertura.

O pipeline pode contar simples execução pela CLI, erro de compilação ou falta de interface como aprovação. Esses casos não comprovam que o código passou no teste.

## Exemplos para conferir

Caminhos a partir da raiz `chatgpt-codesec-analysis/`. Para arquivos que faltam, o caminho indica onde deveriam estar.

| Caso | Caminho relativo |
|---|---|
| Código esperado que falta | `collected_code_6/deepseek-v4-pro-thinking/feedback-static-r1-t1.0-p1.0/heal_0/problem-392-s2.c` |
| Teste sem dizer se passou ou falhou | `collected_code_6/deepseek-v4-pro/feedback-dynamic-r0-t1.0-p1.0/heal_0/problem-108.test.txt` |
| Relatórios do Flawfinder com alertas ignorados | `collected_code_6/claude-fable-5/feedback-static-r0-t1.0-p1.0/heal_0/problem-450.flawfinder.txt` |
| Comentário e relatório diferentes | `collected_code_6/deepseek-v4-pro/feedback-static+dynamic-r0-t1.0-p1.0/heal_1/to_be_healed/problem-102.c` |
| Erro ao rodar a ferramenta | `collected_code_6/qwen-max/feedback-static+dynamic-r0-t0.2-p1.0/heal_0/problem-117-s2.clang.txt` |
| Alerta ligado a outro arquivo | `collected_code_6/deepseek-v4-pro/feedback-static+dynamic-r0-t0.2-p1.0/heal_0/problem-936.gcc.txt` |
| Relatório obrigatório que falta | `collected_code_6/deepseek-v4-pro/feedback-static+dynamic-r0-t0.2-p1.0/heal_0/problem-516.test.txt` |

Códigos ausentes: `problem-392-s2.c`, `problem-510.c`, `problem-510-s2.c`, `problem-510-s3.c`.

Códigos extras: `problem-1.c`, `problem-2.c`.

No Clang, a mensagem observada foi `unable to remove file: Operation not permitted`. Ela indica um erro da ferramenta, mas não prova que toda a análise falhou.

## Como o pipeline se comporta

| Ponto | Funcionamento observado |
|---|---|
| Comentário de teste | Fica acima da função usada no teste, muitas vezes perto do início. Não é um cabeçalho fixo. |
| Medição e feedback | `measure` define os relatórios esperados. `feedback` define os comentários e a fila de cura. |
| Retomada | Pode trocar relatórios dinâmicos e manter comentários antigos. É uma causa possível para diferenças, ainda não comprovada em cada caso. |
| Flawfinder | O parser atual pode ignorar o formato dos alertas. Reproduzir o parser não confirma que os dados estão corretos. |
| Última rodada | Pode deixar uma fila adicional. Isso, sozinho, não significa que faltou executar outra cura. |

Esses são os pontos em que a execução difere da descrição do fluxo.

## Como ler a planilha

`by_configuration.xlsx` tem uma linha por modelo e configuração. `model_comparison.xlsx` coloca os modelos lado a lado e permite escolher a configuração. Cada arquivo funciona sozinho.

Os valores recalculados, os registrados e as diferenças ficam em abas separadas. Recalcular é conferir os valores pelos arquivos; não significa que todos os valores anteriores estavam errados.

**NV** significa não verificável; **Sem registro**, valor ausente da planilha original; **Sem célula**, modelo sem aquela configuração; **N/A**, não se aplica. Ausência de evidência não vira zero.

As contagens de alertas representam arquivos sinalizados pelo pipeline, não vulnerabilidades confirmadas. As taxas de “limpeza” seguem essa mesma regra. Diferença é recalculado menos registrado; para taxas, a planilha usa pontos percentuais.

Tarefas e amostras podem variar mesmo com nomes de configuração parecidos. Confira o total gerado e o contexto antes de comparar modelos.

## Como a checagem foi feita

Os manifests definem tarefas, amostras e rodadas esperadas. Sem eles, a checagem aponta apenas problemas observáveis. ASan e fuzz podem produzir relatórios só em parte dos arquivos; a ausência isolada não comprova erro.

Os comentários foram gerados em memória e comparados com os salvos. A comparação aceita mudança na ordem das mensagens e espaços finais dentro dos comentários. Mudança no código, comentário deslocado, mensagem vazia e linha inválida são checados à parte.

Relatório vazio não prova sucesso. Compilação sem `.o` e resultados finais sem manifest ficam não verificáveis. Dados, pipeline e planilha original foram preservados; não houve nova chamada aos modelos nem execução dos experimentos.

O inventário dos arquivos de entrada e o hash da planilha original permaneceram iguais durante a checagem.

Código consultado: `src/pipeline/comment_inject.py`, `src/dyn/runner.py`, `src/pipeline/run_experiment.py`, `src/analysis/metrics.py` e `docs/architecture.md`.

## Arquivos gerados

| Arquivo | Uso |
|---|---|
| `summary.md` | Leitura rápida dos resultados. |
| `summary.csv` | Uma linha por configuração. |
| `anomalies.csv` | Todos os casos, com caminhos relativos, evidências e ações. |
| `metrics_comparison.csv` | Registrado, recalculado, diferença e motivo. |
| `by_configuration.xlsx` | Uma linha por modelo e configuração. |
| `model_comparison.xlsx` | Modelos lado a lado para a configuração escolhida. |
| `cells/` | Detalhes por arquivo e rodada. |
| `run.json` e `validation.json` | Registro da execução e das verificações. |

## Repetir a checagem

Na pasta do projeto:

```sh
.venv/bin/python -m src.analysis.health_check --all --output-dir reports/code-health
```

Para selecionar um modelo, troque `--all` por `--model NOME`; acrescente `--cell CONFIGURAÇÃO` para uma única configuração. A checagem recalcula a seleção e só substitui cada arquivo de saída depois de terminar de gravá-lo.

O destino não pode ser uma pasta de dados, código ou resultados originais. Código de saída 0: checagem concluída, mesmo com problemas nos dados. Código 2: erro ao executar ou mudança nas entradas.
