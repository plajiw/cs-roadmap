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

https://www.udemy.com/course/docker-essencial-para-a-plataforma-net/learn/lecture/13544578/?udfrontends=true