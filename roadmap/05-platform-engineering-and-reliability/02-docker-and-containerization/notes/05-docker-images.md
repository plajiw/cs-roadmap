# Imagens Docker

Este documento detalha o conceito de imagens Docker, seu sistema de camadas e os métodos para sua criação.

## Conceitos Fundamentais

Containers são sempre baseados em imagens. Uma imagem é o "molde" e o container é a instância em execução.

| Conceito  | Analogia com Programação Orientada a Objetos | Descrição                                                                                                                            |
|-----------|----------------------------------------------|--------------------------------------------------------------------------------------------------------------------------------------|
| **Imagem**  | Classe                                       | Um arquivo binário imutável que inclui todos os requisitos para a criação de um container: código, dependências, bibliotecas e metadados. |
| **Container** | Objeto (instância da classe)                 | Um processo em execução, isolado e baseado em uma imagem. É a instância viva e efêmera da aplicação.                                  |

Toda imagem é composta por uma ou mais camadas somente leitura, organizadas em um **Layered File System**. Uma vez criada, a imagem nunca é modificada.

## Sistema de Camadas (Layered File System)

O principal benefício do sistema de camadas é a reutilização. Se diferentes imagens compartilham a mesma camada base (como um sistema operacional ou um runtime), essa camada é armazenada apenas uma vez no host.

**Vantagens:**
- **Consumo de banda reduzido:** Ao baixar uma nova imagem, apenas as camadas que ainda não existem localmente são transferidas.
- **Economia de espaço em disco:** Camadas compartilhadas não são duplicadas.
- **Builds mais rápidos:** Camadas já existentes são reutilizadas do cache.

### Exemplo: Download de uma imagem

Quando executamos `docker image pull`, o Docker baixa cada camada sequencialmente.

```bash
plajiw@plajiw-notebook:~$ docker image pull nginx
Using default tag: latest
latest: Pulling from library/nginx
448ea5cac5d5: Pull complete 
88d1d984b765: Pull complete 
7b5d674621c2: Pull complete 
4a038fd18db1: Pull complete 
5435b2dcdf5c: Pull complete 
054715a6bffa: Pull complete 
84e114c2bb36: Pull complete 
Digest: sha256:7f0adca1fc6c29c8dc49a2e90037a10ba20dc266baaed0988e9fb4d0d8b85ba0
Status: Downloaded newer image for nginx:latest
docker.io/library/nginx:latest
```
Cada linha com "Pull complete" representa o download de uma camada da imagem `nginx`.

## Camada de Leitura e Escrita (Read/Write Layer)

Se as camadas da imagem são somente leitura, como um container pode modificar arquivos?

Quando um container é criado, o Docker adiciona uma nova camada gravável, chamada **Read/Write Layer**, no topo da pilha de camadas da imagem. Todas as operações de escrita (criar, modificar ou apagar arquivos) ocorrem nesta camada, utilizando uma técnica chamada **Copy-on-Write**.

### Mecanismo Copy-on-Write

1. Quando uma aplicação no container precisa **modificar** um arquivo existente em uma camada somente leitura, o Docker copia esse arquivo para a camada de escrita.
2. A modificação é aplicada na cópia, dentro da camada de escrita.
3. O arquivo original na camada somente leitura permanece intacto, e a versão modificada se torna visível para o container.

Isso garante que a imagem base permaneça imutável, permitindo que múltiplos containers compartilhem a mesma imagem base sem interferir uns nos outros.

## Como Criar Imagens

Existem duas formas principais de criar imagens Docker:

### 1. Processo de Build com `Dockerfile` (Boas Práticas)

Um `Dockerfile` é um arquivo de texto que contém um conjunto de instruções e comandos executados sequencialmente para construir uma imagem. Este é o método recomendado por ser declarativo, versionável e automatizável.

**Comando:**
```bash
docker build -t <nome-da-imagem>:<tag> .
```

### 2. Comando `docker commit` (Não Recomendado)

O comando `docker commit` cria uma nova imagem a partir das alterações feitas na camada de escrita de um container existente.

**Por que não é uma boa prática?**
- **Falta de Transparência:** É difícil saber como a imagem foi gerada, tornando-a uma "caixa preta".
- **Não é Reproduzível:** O processo não é automatizado nem versionado, dependendo de passos manuais.
- **Dificuldade de Manutenção:** Atualizar a imagem se torna um processo complexo e propenso a erros.

Embora útil para depuração rápida ou experimentação, o `docker commit` deve ser evitado em ambientes de produção.