# API EXPERIMENTAL-PROJECT-IN-C

## Indice

  - [1 INTRODUÇÃO](#1-INTRODUÇÃO)
  - [2 DESENVOLVIMENTO](#2-DESENVOLVIMENTO)
    - [2.1 Necessidade de Negócio](#2.1-Necessidade-de-Negócio)
    - [2.2 Proposta Técnica](#2.2-Proposta-Técnica)
    - [2.3 Produção da Aplicação](#2.3-Produção-da-Aplicação)
  - [3 GLOSSÁRIO](#3-GLOSSÁRIO)
  - [REFERÊNCIAS](#REFERÊNCIAS)

## 1 INTRODUÇÃO
Com o intuito de aplicar alguns conhecimentos adiquiridos em C, foi proposta uma necessidade fictícia da construção de um software para venda de ingressos de teatro. A proposta em questão já contém as premissas que devem ser seguidas para atender a necessidade de negócio bem como algumas definições técnicas, tais como a linguagem de programação e a IDE de desenvolvimento que deve ser utilizada.

Para gestão do desenvolvimento foi selecionado o modelo incremental por proporcionar uma entrega faseada da aplicação e uma melhor qualidade nas funcionalidades entregues em cada etapa, visto que os incrementos são testados de forma mais especifica a cada fim de incremento.

Para a prototipação das telas foi utilizada a ferramenta online Figma, já no desenvolvimento do software foi utilizada a IDE Dev C++ e toda a aplicação foi construída com base na linguagem C.

O paradigma de desenvolvimento foi o de linguagens estruturadas, visto que a linguagem C segue esse paradigma.

## 2 DESENVOLVIMENTO

Nesta sessão vamos descrever todo o processo do desenvolvimento do software, desde as necessidades de negócio até o detalhamento da solução técnica que foi entregue.

### 2.1 Necessidade de Negócio

Foi solicitada a construção de um software para venda de ingressos de teatro, tal sistema será composto pelos módulos de venda, comprovante de compra e fluxo de caixa.

O fluxo de venda inicia-se quando o módulo de vendas for acessado, o sistema solicita o preenchimento dos dados do cliente e a escolha da peça teatral e assentos disponíveis. Após o preenchimento e confirmação de compra o sistema apresenta o comprovante da venda e contabiliza no fluxo de caixa a venda realizada. O atendente pode em um segundo momento acessar o módulo de fluxo de caixa para verificar o relatório de vendas realizadas.

Abaixo vamos descrever cada um dos módulos e suas regras de negócio.

Módulo de Venda

Como o nome já diz é aqui que as vendas ocorrerão. A tela desse módulo deverá solicitar o nome do cliente, idade, motivo de meia entrada, opções de espetáculo para serem escolhidos e os assentos disponíveis. Após a confirmação da compra o sistema direciona para o módulo de comprovante da compra.

Na tabela 1 abaixo apresentamos as regras de negócio que está funcionalidade deve contemplar.

Tabela 1 - Regras de negócio do módulo de venda

| **Nome da Regra** | **Detalhamento da Regra** |
| --- | --- |
| Desconto de 50% | Será aplicado caso o cliente esteja enquadrados em um dos seguintes critérios: 1. Para estudantes. 2. Crianças de 2 a 12 anos de idade. 3. Adultos a partir de 60 anos de idade. 4. Professores da rede pública de ensino. |
| Desconto de 100% | Aplicável somente a estudantes carentes no espetáculos que ocorrem as terças-feiras. |
| Escolha da poltrona | O sistema só deve disponibilizar para seleção os assentos que ainda não foram vendidos, evitando assim que mais de uma pessoa tenha o mesmo assento. |
| Exibição das peças disponíveis | O sistema só deve apresentar espetáculos que ainda tem assentos disponíveis, impedindo que peças com lugares esgotados ainda tenham ingressos vendidos. |
| Comportamento após a venda | Assim que a venda é confirmada o sistema deve apresentar a tela de comprovante de compra e contabilizar no fluxo de caixa a venda realizada. |

Fonte: Autor, 2020

Na tabela 2 abaixo apresentamos as regras de validação no preenchimento da interface garantindo assim melhor usabilidade.

Tabela 2 - Regras de validação do módulo de venda

| **Nome da Regra** | **Detalhamento da Regra** |
| --- | --- |
| Campos obrigatórios | Os campos de preenchimento obrigatório para efetuar uma venda são: 1. Nome do cliente. 2. Idade do cliente. 3. Seleção da peça teatral. 4. Seleção do assento. |
| Mensagens de atenção | Caso algum dos campos obrigatórios não seja preenchido, uma mensagem deve ser exibida informando o campos que precisam ser preenchidos. |

Fonte: Autor, 2020

##### Módulo de Comprovante de Compra

Esse módulo deve ser executado automaticamente após a conclusão de uma venda, ou seja, ele deve exibir o comprovante de compra do ingresso da peça teatral.

As informações que devem ser exibidas são a data e hora do espetáculo, nome da peça teatral, código do assento selecionado, valor pago e o desconto caso haja.

##### Módulo de Fluxo de Caixa

Esse módulo não faz parte do fluxo da venda, mas pode ser acessado a qualquer momento pelo atendente para verificar as vendas que foram efetuadas.

Nessa tela deverão ser exibidas todas as vendas realizadas no dia, em uma lista contendo o nome do cliente, nome da peça teatral, valor do ingresso, percentual de desconto, valor pago. No fim dessa lista deve haver um totalizador que mostra o total arrecadado.

### 2.2 Proposta Técnica

Para atender a necessidade de negócio, foi definido que o modelo de gestão do projeto será o incremental, ou seja, todo o processo de desenvolvimento será dividido em três incrementos, onde cada incremento corresponde a uma funcionalidade que será entregue até que todo o software esteja completo.

Na perspectiva do desenvolvimento ou codificação será usada a linguagem C por meio da IDE Dev C++. Será produzida uma aplicação Windows Application, ou seja, um software que será executado somente em ambiente Windows por meio de interfaces gráficas.

Modelo de Ciclo de Vida Incremental

Neste modelo de ciclo de vida a construção da aplicação é dividida em pequenas partes onde o modelo cascata é aplicado a cada incremento.

Então a cada incremento serão aplicados os passos conforme tabela 3.

Tabela 3 - Passos do modelo incremental

| **Ordem** | **Nome** | **Descrição** |
| --- | --- | --- |
| 1 | Comunicação | Levantamento dos requisitos e comunicação do desenvolvedor com o cliente. |
| 2 | Planejamento | Define-se a melhor técnica de desenvolvimento bem como o cronograma. |
| 3 | Modelagem | Construção do modelo que ajuda ao cliente e desenvolvedor entender melhor os requisitos que vão atender as necessidades do negócio. |
| 4 | Construção | Aqui envolve a codificação e os testes do que foi produzido. |
| 5 | Implantação | O software é entregue ao cliente que avalia e da seu feedback. |

Fonte: Autor, 2020

As vantagens de se usar esse modelo de gestão são:

- Entregas pequenas facilitam a identificação e correção de problemas.
- Requisitos não identificados inicialmente podem ser aplicados nos incrementos.
- Cada interação já agrega valor ao produto final.
- Os feedbacks de incrementos anteriores, podem facilitar nos incrementos posteriores.
- Os incrementos podem ser produzidos por equipes mais enxutas.
- A entrega em incrementos permite o cumprimento de prazos mais específicos e que a equipe seja mais assertiva em seus prazos.

Agora vamos descrever quais serão os incrementos envolvidos na produção do software.

##### Primeiro Incremento

No primeiro incremento serão produzidos os protótipos de todas as funcionalidades, também será produzida a janela principal contendo o menu e barra de status, bem como o módulo de venda dos ingressos.

##### Segundo Incremento

No segundo incremento será produzido o módulo de comprovante de pagamento e o mesmo será incorporado ao processo de venda, de modo que assim que a venda for finalizada a tela do comprovante será apresentada.

##### Terceiro Incremento

No terceiro incremento será produzido o fluxo de caixa de modo que o mesmo poderá ser acessado a qualquer momento para verificar as vendas que foram efetuadas e o total arrecadado.

### 2.3 Produção da Aplicação

Aqui vamos demonstrar algumas características da aplicação, tais como os protótipos de tela, estrutura da solução e como o código foi organizado.

Protótipos das Telas

Abaixo seguem as imagens que descrevem como serão as interfaces da aplicação.

Figura 1 - Tela inicial do sistema

<img src="https://github.com/macgyver1985/experimental-project-in-c/blob/master/docs/tela_1.jpg" alt="Tela 1" width="600">

Fonte: Autor, 2020

Figura 2 - Tela do módulo de vendas

<img src="https://github.com/macgyver1985/experimental-project-in-c/blob/master/docs/tela_2.jpg" alt="Tela 2" width="600">

Fonte: Autor, 2020

Figura 3 - Tela do módulo do comprovante de compra

<img src="https://github.com/macgyver1985/experimental-project-in-c/blob/master/docs/tela_3.jpg" alt="Tela 3" width="600">

Fonte: Autor, 2020

Figura 4 - Tela do módulo do fluxo de caixa

<img src="https://github.com/macgyver1985/experimental-project-in-c/blob/master/docs/tela_4.jpg" alt="Tela 4" width="600">

Fonte: Autor, 2020

Estrutura da Solução

Todo desenvolvimento foi feito por meio da IDE Dev C++, abaixo figura 5 que mostra como os artefatos estão organizados dentro da solução.

Figura 5 - Organização da solução

<img src="https://github.com/macgyver1985/experimental-project-in-c/blob/master/docs/folders.jpg" alt="Solução" width="600">

Fonte: Autor, 2020

Agora vamos entender o que contem em cada arquivo do projeto:

- main.c: Trata-se do arquivo inicial do programa, onde existe a função main que é executada na inicialização da aplicação.
- menu.rc: Contém a configuração do menu da aplicação.
- resources.h: Contém a identificação de todos os campos dos formulários bem como as estruturas de dados que são usadas na aplicação e as funções que manipulam essas estruturas.
- database.h: Contém as coleções de dados que são usadas no sistema, por exemplo os assentos disponíveis.
- util.h: Contém as funções que auxiliam a construção dos formulários usados nas telas.
- viewBox.h: Contém toda a programação do módulo de fluxo de caixa.
- viewPurchase.h: Contém toda a programação do módulo de comprovante de pagamento.
- viewSales.h: Contém toda a programação para o módulo de venda.

Estrutura de Pastas da Solução

Aqui vamos descrever a estrutura de pastas da aplicação. Veja a figura 6 e as explicações.

Figura 6 - Estrutura de pastas da solução

<img src="https://github.com/macgyver1985/experimental-project-in-c/blob/master/docs/folders_2.jpg" alt="Estrutura de Pastas" width="600">

Fonte: Autor, 2020

Agora vamos entender a estrutura:

- TicketSales.dev: Este é o arquivo de solução do Dev C++, é apenas usado para abrir a solução através da IDE.
- build: Pasta onde fica a compilação do código fonte.
- dist: Pasta onde fica o executável que é gerado. É aqui que fica a versão de distribuição da aplicação, ou seja, para executá-la basta executar o arquivo TicketSales.exe existente dentro dessa pasta.
- src: É aqui que ficam os arquivos fontes da aplicação.

## 4 GLOSSÁRIO

Figma: Ferramenta WEB usada para construção de protótipos de telas.

IDE: Ambiente de Desenvolvimento Integrado.

## REFERÊNCIAS

[https://docs.microsoft.com/en-us/windows/win32/](https://docs.microsoft.com/en-us/windows/win32/), data de acesso em 20 de Maio de 2020.

[https://www.devmedia.com.br/ciclos-de-vida-do-software/21099](https://www.devmedia.com.br/ciclos-de-vida-do-software/21099), data de acesso em 20 de Maio de 2020.
