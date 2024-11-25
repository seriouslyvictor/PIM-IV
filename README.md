# PIM IV - Projeto Integrado Multidisciplinar IV

Este é um projeto universitário desenvolvido como parte do curso de **Análise e Desenvolvimento de Sistemas** da **UNIP**, para a disciplina de **Projeto Integrado Multidisciplinar IV (PIM IV)**. O objetivo deste projeto é desenvolver um sistema para gerenciar informações de empresas, incluindo dados como nome, CNPJ, telefone, endereço e dados mensais de tratamento de resíduos e custos.

## Descrição do Projeto

O sistema foi desenvolvido para armazenar, carregar e exibir informações de diversas empresas e seus dados mensais. Cada empresa possui os seguintes dados principais:
- Nome
- CNPJ
- Telefone
- Endereço (rua, bairro, cidade, estado, CEP)
- Email

Além disso, o sistema armazena dados mensais de tratamento de lixo e custos relacionados a cada empresa, com capacidade para armazenar dados de até 12 meses.

### Funcionalidades
- **Cadastro de Empresas**: Leitura e armazenamento de dados das empresas a partir de um arquivo de texto.
- **Relatório por Empresa**: Exibição de informações detalhadas de cada empresa, incluindo seus dados mensais de tratamento de lixo e custos.
- **Validação de Dados**: O sistema verifica se os dados estão no formato correto e exibe mensagens de erro ou aviso quando necessário.

## Como Usar

### Pré-requisitos

Para rodar este projeto, é necessário ter um compilador C (como GCC) instalado no seu computador. Além disso, é importante ter um arquivo de dados com o formato adequado para carregar as informações corretamente.

### Compilação e Execução

1. Clone este repositório em seu computador:

   ```bash
   git clone https://github.com/seu-usuario/pim-iv.git
2. Acesse o diretório do projeto:
   ```bash
   cd pim-iv
3. Compile o código utilizando o comando gcc (ou outro compilador de sua preferência):
   ```bash
   gcc -o pimiv main.c
5. Execute o programa:
   ```bash
   ./pimiv
## Formato do Arquivo de Entrada
O sistema espera um arquivo de texto com os dados das empresas no seguinte formato:
  ```txt
  Nome: [Nome da Empresa], CNPJ: [CNPJ], Telefone: [Telefone], Endereço: [Endereço], Bairro: [Bairro], Cidade: [Cidade], Estado: [Estado], CEP: [CEP], Email: [Email]
  - Mês: [Mês], Tratamento: [Quantidade de Lixo] toneladas, Custo: [Custo] reais
  - Mês: [Outro Mês], Tratamento: [Quantidade de Lixo] toneladas, Custo: [Custo] reais
  ###END_COMPANY###
  ```

## Estrutura do Projeto
  - main.c: Arquivo principal contendo a implementação das funções para carregar e exibir os dados das empresas.
  - data.txt: Exemplo de arquivo de entrada com dados das empresas (a ser criado ou fornecido pelo usuário).
  - README.md: Este arquivo, com informações sobre o projeto.

### Contato
Se você tiver alguma dúvida ou sugestão sobre o projeto, fique à vontade para entrar em contato via e-mail: schiavovictor@outlook.com.
