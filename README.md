


-------------------------------------
   Aplicação PHPServerNumberFull
-------------------------------------

Aplicação: Números Por Extenso
Objetivo: Cumprir o desafio de criar um servidor HTTP que, para cada requisição GET, retorne um JSON cuja chave "extenso" seja a versão por extenso do número inteiro enviado no path. 

Exemplos:
λ curl http://localhost:3000/1
{ "extenso": "um" }

λ curl http://localhost:3000/-1042
{ "extenso": "menos mil e quarenta e dois" }

λ curl http://localhost:3000/94587
{ "extenso": "noventa e quatro mil e quinhentos e oitenta e sete" }

Requisitos:
1 - os números podem estar no intervalo [-99999, 99999];
2 - os "e"s separando milhares, centenas e dezenas (vide exemplo): "noventa e quatro mil e quinhentos e oitenta e sete". Esse não é o padrão da norma culta da língua portuguesa, e isso é intencional;
3 - é esperado que o código implemente o algoritmo de tradução;
4 - edge cases
5 - tratamento de erros
6 - testes unitários
7 - estruturação
8 - qualidade do código
9 - uso do git
10- ambiente Docker


Estrutura de Diretórios
---app                   #pasta com a aplicação 
   |___idiomas           #pasta com arquivos de idiomas
       |____pt_dados.inc #arquivo idioma Português   
       |____en_dados.inc #arquivo idioma Inglês   
       |____es_dados.inc #arquivo idioma Espanhol
       |____fr_dados.inc #arquivo idioma Francês
   |___index.php         #responde à requisição
   |___logica.inc        #contem processamento  
   |___respostas_http.inc#contem cabeçalhos HTTP e Resposta JSON  
   |___socket.php        #tentativa de usar socket como servidor HTTP     
---docker                #pasta com o Recurso para utilizar a opção de Conteiner Docker 
   |___Dockerfile        #arquivo para criar a Imagem Docker
---testes                #pasta com testes Unitários
   |___teste.php         #arquivo que executa testes unitários
README.md                #este arquivo com descrição do projeto   


Sugestão de Passo a passo:
-----------------------------
     Utilizando o Git
-----------------------------
Baixar a pasta "app" e a pasta "docker" pasta uma pasta local

-----------------------------
   Utilizando o DockerToobox
-----------------------------

                        ##         .
                  ## ## ##        ==
               ## ## ## ## ##    ===
           /"""""""""""""""""\___/ ===
      ~~~ {~~ ~~~~ ~~~ ~~~~ ~~~ ~ /  ===- ~~~
           \______ o           __/
             \    \         __/
              \____\_______/

Pelo console do Docker:
1-acesar a pasta "docker" na pasta local
$ cd C:/EDSON/TESTDOCKER/ServerMakedInPHPV2/app
2-digitar o comando para Criar a Imagem pelo Dockerfile:
$ docker build -f ../docker/Dockerfile -t img_php_server_number_full .
3-digitar o comando para criar o Container pela Imagem criada:
$ docker run -tid -p 3000:3000 --name contPHPServerNumberFull img_php_server_number_full 
4-digitar o comando para startar o servidor PHPServerNumberFull
$ docker exec -d contPHPServerNumberFull /usr/local/bin/php -S localhost:3000
5-digitar o comando para acessar o servidor
$ docker container exec -it contPHPServerNumberFull bash
6-digitar os comandos para testar o servidor
curl http://localhost:3000/1
7-para trocar o idioma para Inglês, digite o comando
curl -H 'Accept-Language: en' http://localhost:3000/1 


~~~~~~~~~~~~~~~~~~~~~~~~~~

