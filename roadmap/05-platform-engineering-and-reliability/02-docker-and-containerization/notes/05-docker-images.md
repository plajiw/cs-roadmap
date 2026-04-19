# Imagens Docker

Este documento detalha o conceito de imagens Docker, seu sistema de camadas e os métodos para sua criação.

## Conceitos Fundamentais

Containers são sempre baseados em imagens. Uma imagem é o "molde" e o container é a instância em execução.

| Conceito      | Analogia com Programação Orientada a Objetos | Descrição                                                                                                                                 |
|---------------|----------------------------------------------|-------------------------------------------------------------------------------------------------------------------------------------------|
| **Imagem**    | Classe                                       | Um arquivo binário imutável que inclui todos os requisitos para a criação de um container: código, dependências, bibliotecas e metadados. |
| **Container** | Objeto (instância da classe)                 | Um processo em execução, isolado e baseado em uma imagem. É a instância viva e efêmera da aplicação.                                      |

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

## Dockerfile

### Por que usar Dockerfile

Nem sempre a imagem que desejamos usar está pronta da maneira que queremos. Muitas vezes é necessário ter uma imagem customizada com dependências, configurações e comportamentos específicos do projeto.

Um **Dockerfile** é um arquivo de texto que contém instruções e comandos para construir uma imagem Docker automaticamente. Nele, definimos regras, informações e instruções que ficarão contidas na imagem final. As instruções são interpretadas linha por linha.

### Conceito: Processo de Build

O processo de build (Dockerfile → Image) atua no contexto do diretório onde o Dockerfile está localizado e seus subdiretórios. Docker lê as instruções sequencialmente e cria uma camada para cada uma delas.

### Instruções comuns do Dockerfile

| Instrução | Descrição |
|-----------|-----------|
| `FROM <imagem>` | Define a imagem base para construção |
| `LABEL <chave>=<valor>` | Adiciona metadados à imagem (versão, descrição) |
| `RUN <comando>` | Executa comando durante o build (instalações, setup) |
| `WORKDIR <caminho>` | Define diretório de trabalho padrão no container |
| `COPY <origem> <destino>` | Copia arquivos do host para a imagem |
| `ADD <origem> <destino>` | Similar a COPY, mas com suporte a URLs e descompactação |
| `ENV <chave>=<valor>` | Define variável de ambiente |
| `EXPOSE <porta>` | Documenta qual porta a aplicação usa (não publica) |
| `CMD <comando>` | Define comando padrão de execução |
| `ENTRYPOINT <comando>` | Define o executável principal |

### Exemplo prático: Construir imagem Nginx customizada

Objetivo: Criar uma imagem baseada em Debian que instale e inicie um servidor Nginx.

**Etapas do projeto:**

1. Definir imagem base (Debian 12)
2. Definir metadados (versão, descrição)
3. Executar comando para instalar Nginx
4. Exportar a porta que o servidor vai usar
5. Definir o comando padrão de inicialização

**Dockerfile:**

```dockerfile
FROM debian:12
LABEL version="1.0" description="debian/nginx"
RUN apt-get update && apt-get install -y nginx && apt-get clean
EXPOSE 80
CMD ["nginx", "-g", "daemon off;"]
```

**Leitura do Dockerfile:**

- `FROM debian:12`: Usa Debian 12 como base
- `LABEL version="1.0"`: Adiciona rótulo de versão à imagem
- `RUN apt-get update && apt-get install -y nginx`: Instala Nginx
- `apt-get clean`: Remove cache de pacotes para reduzir tamanho
- `EXPOSE 80`: Documenta que nginx usa porta 80
- `CMD ["nginx", "-g", "daemon off;"]`: Nginx executa em foreground (não como daemon)

### Construindo a imagem

Use o comando `docker build` para construir a imagem a partir do Dockerfile:

```bash
docker build -t debianNginx/img:1.0 .
```

**Parâmetros:**
- `-t debianNginx/img:1.0`: Tag (nome e versão) da imagem
- `.`: Contexto (diretório onde o Dockerfile está)

**Saída esperada:**

```bash
[+] Building 45.2s (7/7) FINISHED
...
```

### Verificando a imagem criada

Liste as imagens para confirmar o build:

```bash
docker images
```

**Exemplo de saída:**

```
REPOSITORY                       TAG       IMAGE ID       CREATED          SIZE
debianNginx/img                  1.0       56353255bf3e  16 seconds ago   243MB
```

### Executar container a partir da imagem

```bash
docker container run -d -p 8080:80 --name ws1 debianNginx/img:1.0
```

**Saída (ID do container):**

```
95a30cb71e258f242efd26076222049675ad275bd73af9a5c82cfe474c77be23
```

Agora o servidor Nginx está rodando na porta 8080 do host.

## Gerenciando Imagens

### Listar imagens

```bash
docker images
docker image ls
```

Ambos os comandos listam todas as imagens armazenadas localmente.

### Download de imagens (docker pull)

```bash
# Baixar versão mais recente (latest)
docker image pull redis

# Baixar versão específica
docker image pull redis:7.0
```

### Inspecionar detalhes de uma imagem

```bash
docker image inspect debianNginx/img:1.0
```

**Exemplo de saída (campos principais):**

```json
[
  {
    "Id": "sha256:56353255bf3e733d9280d5037760cd02c46c81e23cdceee0ead3fced0df6ea40",
    "RepoTags": ["debianNginx/img:1.0"],
    "Created": "2026-04-14T15:40:33.697375251Z",
    "Architecture": "amd64",
    "Os": "linux",
    "Size": 70925831,
    "RootFS": {
      "Type": "layers",
      "Layers": [
        "sha256:eaa7304345ff8f4a9b0628fc5c0cde472ffac173a24e660e3b0b98d9c38eeb83",
        "sha256:b7def884a88c12a8400596c608354629e15db5b8fcaae704a0241cda65e8b5c7"
      ]
    },
    "Config": {
      "Cmd": ["nginx", "-g", "daemon off;"],
      "ExposedPorts": {"80/tcp": {}},
      "Labels": {"description": "debian/nginx", "version": "1.0"}
    }
  }
]
```

| Campo | Significado |
|-------|-------------|
| `Id` | Identificador único da imagem (SHA256) |
| `RepoTags` | Nomes/tags da imagem no repositório local |
| `Size` | Tamanho total da imagem em bytes |
| `Architecture` | Arquitetura (amd64, arm64, etc.) |
| `Os` | Sistema operacional base |
| `RootFS.Layers` | Camadas que compõem a imagem |
| `Config.Cmd` | Comando padrão de execução |
| `Config.ExposedPorts` | Portas documentadas |
| `Config.Labels` | Metadados customizados |

### Histórico de camadas

```bash
docker image history debianNginx/img:1.0
```

Mostra cada camada e como a imagem foi construída (útil para debugging e otimização).

### Criar alias (tag) para imagem

```bash
docker image tag redis:latest redis:current
```

Neste exemplo, `redis:current` é um alias (referência) para `redis:latest`. Ambas apontam para a mesma imagem.

## Publicando Imagens

### Fazer login no Docker Hub

```bash
docker login
```

Insira suas credenciais (username e senha do Docker Hub).

### Publicar imagem no repositório

```bash
docker push <nome-da-imagem>:<tag>
```

**Exemplo:**

```bash
docker push debianNginx/img:1.0
```

A imagem será armazenada no Docker Hub e poderá ser acessada por outros usuários (dependendo das configurações de privacidade).

## Aplicação ASP.NET Core MVC

Esta seção demonstra como containerizar uma aplicação ASP.NET Core MVC com Docker, desde a criação do projeto até a publicação em repositório.

**Pré-requisitos:**
- .NET Core SDK 8
- Visual Studio Code
- Docker instalado e configurado

### Criar projeto ASP.NET Core MVC

```bash
mkdir projetos
cd projetos
mkdir mvc1
cd mvc1
dotnet new mvc
code .
```

Este comando cria um novo projeto MVC padrão do ASP.NET Core.

### Publicar para Release

Antes de containerizar, é necessário compilar a aplicação para uma distribuição otimizada:

```bash
dotnet publish -c Release -o dist
```

**O que acontece:**
- `-c Release`: Compila em modo Release (otimizado para produção)
- `-o dist`: Coloca os binários compilados na pasta `dist`
- `mvc1.dll`: Arquivo principal gerado (ponto de entrada da aplicação)

Verifique o conteúdo:

```bash
cd dist
ls -la
```

### Criar Dockerfile

Na raiz da aplicação, crie um arquivo `Dockerfile` para definir a imagem:

```dockerfile
FROM mcr.microsoft.com/dotnet/aspnet:8.0
WORKDIR /app
COPY dist/ .
ENV ASPNETCORE_HTTP_PORTS=80
ENTRYPOINT ["dotnet", "mvc1.dll"]
```

**Explicação das instruções:**

| Instrução | Propósito |
|-----------|----------|
| `FROM mcr.microsoft.com/dotnet/aspnet:8.0` | Imagem base: runtime ASP.NET Core 8.0 |
| `WORKDIR /app` | Define `/app` como diretório de trabalho do container |
| `COPY dist/ .` | Copia binários compilados para `/app` |
| `ENV ASPNETCORE_HTTP_PORTS=80` | Configura a porta HTTP como 80 |
| `ENTRYPOINT ["dotnet", "mvc1.dll"]` | Define `mvc1.dll` como executável principal |

### Construir a imagem

```bash
docker build -t mvc1/app1:1.0 .
```

**Parâmetros:**

- `-t mvc1/app1:1.0`: Tag (nome do repositório / nome da imagem e versão)
- `.`: Contexto (diretório onde o Dockerfile está localizado)

Verifique se a imagem foi criada:

```bash
docker images
```

**Exemplo de saída:**

```
REPOSITORY         TAG      IMAGE ID       SIZE
mvc1/app1          1.0      66c8226d99f6   321MB
```

### Executar container

Existem duas formas equivalentes de executar o container:

**Opção 1: Usar `docker run` diretamente**

```bash
docker run -d -p 3000:80 --name mvcproduto mvc1/app1:1.0
```

**Opção 2: Criar e depois iniciar**

```bash
docker container create -p 3000:80 --name mvcproduto mvc1/app1:1.0
docker container start mvcproduto
```

**Parâmetros:**

| Parâmetro | Descrição |
|-----------|-----------|
| `-d` | Executa em modo detached (background) |
| `-p 3000:80` | Mapeia porta 80 do container para porta 3000 do host |
| `--name mvcproduto` | Nome do container |

### Verificar execução

```bash
docker logs mvcproduto
curl -I http://localhost:3000
```

O comando `docker logs` exibe os logs do container, e `curl -I` verifica se a aplicação está respondendo na porta 3000.

### Publicar imagem no Docker Hub

Para compartilhar a imagem com outros usuários, publique-a no Docker Hub.

**1. Criar conta no Docker Hub**

Acesse [docker.io](https://hub.docker.com) e crie uma conta.

**2. Fazer login localmente**

```bash
docker login -u <usuario> -p <senha>
```

**3. Etiquetar a imagem para o repositório**

```bash
docker image tag mvc1/app1:1.0 <usuario>/mvc1/app1:1.0
```

**4. Enviar para o Docker Hub**

```bash
docker push <usuario>/mvc1/app1:1.0
```

A imagem agora está disponível publicamente (ou privadamente, conforme suas configurações de privacidade no Docker Hub).