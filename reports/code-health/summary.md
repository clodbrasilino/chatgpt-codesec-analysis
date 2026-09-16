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

As quantidades acima contam ocorrências ao longo das rodadas. Um arquivo pode aparecer em mais de um problema; não some tudo como se fossem arquivos diferentes.

Os exemplos com caminhos relativos e o método estão em `report.md`. Todos os casos estão em `anomalies.csv`.

São dois arquivos: `by_configuration.xlsx` e `model_comparison.xlsx`. Os valores recalculados, os registrados e as diferenças ficam em abas separadas. Recalcular é conferir os valores pelos arquivos; não significa que todos os valores anteriores estavam errados.
