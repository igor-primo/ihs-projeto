IHS

. Explicação

O projeto consistiu em modificar o scritp 'gesture.ts' do projeto
https://github.com/vladmandic/human adicionando uma funcionalidade à
função que captura gestos de cabeça (função 'face'). A modificação envia
um número inteiro em um cabeçalho HTTP baseado no tipo de gesto de face que
foi detectado (0 se 'facing left', 1 se 'facing right', 2 se 'head up', 3 se
'head down', 4 se 'blink') e o envia para o servidor na pasta ./back/server.
Esse servidor captura o cabeçalho e envia o comando apropriado para o programa
't', que realizará a função correta de mouse, como já descrito.

. Instalação

Você deve ter o projeto https://github.com/vladmandic/human instalado
localmente. Então deve substituir 'human/src/gesture/gesture.ts' pelo script em
./front. ./back/t.c deve ser compilado ('gcc t.c -o t'). Você deve possuir
'node' versão v16.17.1. Com o comando 'npm i' executado num terminal na pasta
./back/server você deve instalar as dependências para executar o servidor.

. Execução

Com um terminal na pasta ./back/server você pode executar 'node index.js' para
inicializar o servidor. Com outro terminal na pasta
'human' (raiz do projeto), e com o script novo instalado em
'human/src/gesture/gesture.ts'
você pode executar 'npm run dev' para compilar o código e e executá-lo.
Com o programa executando, você pode abrir o navegador e para o recurso
'http://localhost:10030/demo/typescript' para ver algumas coisas misteriosas.

A compilação do projeto pode requerer a modificação da variável 'production' para
'false' em 'human/.npmrc' e a instalação de dependências com 'npm i'.
