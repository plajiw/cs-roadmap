no linux é ncessario passar o sudo sempre
sudo groupadd docker
sudo gpasswd -a <user> docker
sudo service docker restart
newgrp Docker

docker run --help

docker container run <nome da imagem>
não mantem ativo, só executa e encerra

criar um container a partir de uimagem que serpa baixada a partir de um repositorio d eimagens docker hub, uma imagem pronta
docker container run hello-world

https://hub.docker.com/_/hello-world

docker images
hello-world                      latest                   452a468a4bf9   2 weeks ago   20.4kB

docker container ls -a em não execução

Atuando com o modo cliente do docker usando a interface de linha de comando que é fornecida pelo API Rest do Docker Daemon

docker, é o executor do comando
container, indica que o comandovai atuar em um container
run é a porta de entrada no Docker e realiza 4 operações
    baixa a imagem não encontrada localmente: docker image pull
    criar o container: docker container create
    inicailiza o container: docker container start
    uso do modo interativo executa um comanod: docker container exec

hello-world é o nome da imagem existente na docker hub utilizada parac riação do container

docker container ps - exibe todos em execuçaõ
docker container ps -a -  exibe todos os container

docker images
exibe as imagens obtidas em nossa sistema para criação de outros continaers

docker container run

docker image pull para trazer a imagem
docker image pull alpine // sem parametro pega a mais receente... pull alpine:3.18
docker container run alpine ls -l // ja cria o container e faz o comando ls -l

docker engine inicou o container e enviou o coando ls -l dentro do container

docker container run -it alpine /bin/sh

-i intereative -t terminal ou -it

um contaier nn tem como integragir com outros container, mesmo contendo as mesma imagens

docker container start <id ou name>

docker container exec 3b9a5940af6567955054638d94a41df394b5effe95c92fa1f5faaae6c147f5eb ls -l // executa o comando dentro do container

docker container stop beautiful_poincare

docker container run --name plajiw alpine // criado com nome especifico
docker container rm plajiw

docker --help
docker container run --help

## Mapear Portas dos Containers

Um conainer tem como objetivo empacotar, isolar sua aplicação e dependecias para poder execular em qualquer lugar. Embora o isolamento seja sua principal caracteriste

Um container completamente isolado e inacessivel seria pouco util. Por isso, podemos compartilhar recursos e acessar o container temos que permitri de alguma forma que ela possa ser acessada pelo "mundo exterior"

docker container run --name ws1 -p 8080:80 nginx

run, comando que cria o container
--name ws1, comando que especifica o nome do container
-p 8080:80, especifica a porta que estamos expondo
nginx, nome da imaeghme obtida no repositorio

8080 -> Porta que estamos expondo para fora do container
80 -> Porta interna do container

nesse exemplo, o container ws1 é criado a partir da imagem nginx, e a porta 80 do container é mapeada para a porta 8080 do host. Isso significa que qualquer solicitação feita para localhost:8080 no host será redirecionada para a porta 80 dentro do container, onde o servidor nginx está escutando.

http://localhost:8080/

exceutar um container em segundo-plano
docker container run --name ws1 -p 8080:80 -d nginx

Não permite repetições de nomes
docker container run --name ws2 -p 8080:80 -d nginx

e não permite criar container em mesmas postas