# Simulador de Cash Dispenser (ATM)
 
Projeto da disciplina **Algoritmos e Pensamento Computacional** (UNICSUL, 2026-2): Programa de Controle de Fluxo.
 
O programa simula o controle interno de notas de um caixa eletrônico: armazena o estoque de cada denominação (10, 20, 50 e 100), permite reabastecer, exibir o estoque, sacar dinheiro e consultar o histórico de operações. Não processa cartões, transferências nem pagamentos.
 
> **Versão atual: somente terminal (sem parte visual).**
> Esta é a versão em linguagem C executada no console, sem interface gráfica. O **site com o código-fonte C está em desenvolvimento** e será disponibilizado em uma versão futura.
 
## Funcionalidades
 
| Opção | Operação | Descrição |
|-------|----------|-----------|
| 0 | Exibir Notas Disponíveis | Mostra a quantidade de notas de 10, 20, 50 e 100 |
| 1 | Abastecer ATM | Soma a quantidade informada ao estoque (`<enter>` vazio = nenhuma nota) |
| 2 | Sacar Dinheiro | Calcula uma combinação válida de notas; nega o saque se não houver combinação |
| 3 | Exibir Histórico | Lista saques e abastecimentos com valor, data e hora |
| 9 | Sair | Encerra o programa |
 
### Regras e validações
 
- O valor do saque deve ser **múltiplo de 10** e maior que zero.
- O saque prefere as notas de maior valor, mas testa outras combinações antes de negar.
- Quantidades negativas no abastecimento são rejeitadas.
- Opções de menu inválidas (letras, enter vazio, números fora do menu) exibem aviso.
- O histórico guarda até 100 operações.
## Estrutura de pastas
 
```
simulador_cash_dispenser/
├── c/
│   └── codigo-fonte.c      # Código-fonte do simulador
├── img - testes/           # Printscreens das simulações de saque
└── README.md               # Este arquivo
```
 
## Como executar
 
### Requisitos
 
- Compilador C (GCC, por exemplo)
- Terminal (Linux, macOS ou Windows)
### Linux / macOS
 
```bash
cd c
gcc codigo-fonte.c -o codigo-fonte
./codigo-fonte
```
 
### Windows (GCC / MinGW)
 
```bash
cd c
gcc codigo-fonte.c -o codigo-fonte.exe
codigo-fonte.exe
```
 
### Dev-C++
 
Abra `c/codigo-fonte.c`, compile e execute com **F11**. Se os acentos aparecerem com caracteres estranhos, adicione `#include <locale.h>` e `setlocale(LC_ALL, "Portuguese");` no início da função `main`.
 
## Exemplo de uso
 
Abastecendo 1 nota de cada valor e sacando 180:
 
```
Escolha uma operação: 1
Notas 10: 1
Notas 20: 1
Notas 50: 1
Notas 100: 1
 
Escolha uma operação: 2
Digite o valor do Saque: 180
 
Saque realizada com sucesso
Valor do Saque: 180
 Notas 10: 1
 Notas 20: 1
 Notas 50: 1
 Notas 100: 1
```
 
## Testes realizados
 
Os printscreens estão na pasta `img - testes/`:
 
1. Saque com sucesso e estoque completo (180).
2. Saque com sucesso sem notas de 50 (180).
3. Saque negado por falta de notas (ex.: 120 com apenas 1 nota de 100).
4. Valor inválido (não múltiplo de 10, zero ou negativo).
## Bibliotecas utilizadas
 
- `stdio.h`: entrada e saída (`printf`, `fgets`)
- `stdlib.h`: conversão de texto em número (`atoi`)
- `string.h`: cópia de texto (`strcpy`)
- `time.h`: data e hora (`time`, `localtime`, `strftime`)
## Próximos passos
 
- Publicar o **site com o código-fonte C** (em desenvolvimento).
- Criar a parte visual do simulador.
 