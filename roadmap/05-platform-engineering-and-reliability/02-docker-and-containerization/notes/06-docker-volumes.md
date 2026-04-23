# Docker Volumes

Este documento detalha o conceito de volumes no Docker, sua importância para persistência de dados e os métodos de mapeamento.

## Conceitos Fundamentais

### O Problema: Perda de Dados ao Remover Containers

Containers são criados a partir de imagens e possuem uma fina camada de leitura e escrita no topo das camadas de imagem, que são somente leitura e imutáveis. Quando removemos um container com `docker container rm`, essa camada de leitura/escrita é também removida, e **todas as informações contidas nela são perdidas permanentemente**.

Isso cria um problema crítico: como persistir dados de aplicações, logs, código ou banco de dados?

| Problema | Descrição |
|----------|-----------|
| **Perda de dados** | Remover um container deleta todos os dados gerados durante sua execução |
| **Impossibilidade de atualizar** | Não é possível substituir um container sem perder dados associados |
| **Falta de compartilhamento** | Dados não podem ser compartilhados entre containers ou com o host |

### O Volume: Solução para Persistência

**Volumes** são mecanismos Docker para armazenar e persistir dados separando-os do container. Um volume:

- **Separa dados gerados pela aplicação** do armazenamento do container
- **Permite persistência** — dados sobrevivem à remoção do container
- **Facilita compartilhamento** — entre host e container, ou entre múltiplos containers

### Arquitetura: Container, Host e Volume

A relação entre container, Docker host e volume funciona da seguinte forma:

1. O **Docker host** gerencia um **volume** (pasta no sistema de arquivos do host)
2. O **container** monta esse volume em um de seus caminhos internos
3. Toda informação escrita nesse caminho é armazenada no volume do host, não na camada do container
4. Se o container for removido, o volume persiste no host

## Mapeamento de Volumes (Bind Mounts)

### Conceito: O que é um Bind Mount?

Um **bind mount** conecta um diretório arbitrário do **host** diretamente a um caminho dentro do **container**. O desenvolvedor especifica exatamente qual pasta do host será montada.

**Diferença crítica em relação a Docker Volumes:**

| Aspecto | Bind Mount | Docker Volume |
| ------- | ---------- | ------------- |
| **Localização** | Qualquer pasta do host (ex: `/home/user/projeto`) | Pasta gerenciada pelo Docker (`/var/lib/docker/volumes/`) |
| **Controle** | Desenvolvedor define o caminho exato | Docker decide onde armazenar |
| **Portabilidade** | Depende de caminho absoluto do host | Portável entre hosts |
| **Performance** | Mais lento (syscalls do host) | Mais rápido (kernel Linux otimizado) |
| **Caso de uso** | Desenvolvimento (hot-reload de código) | Produção (dados persistentes) |

**Visualização:**

```text
Host                          Container
┌─────────────────┐           ┌──────────────┐
│ /home/user/app  │──────────→│  /app/code   │
│  (seus arquivos)│ bind mount│ (sincronizado)│
└─────────────────┘           └──────────────┘
   (você controla)              (vê mudanças em tempo real)
```

### Casos de Uso de Bind Mount

- **Desenvolvimento local**: Código no host, container executa mudanças imediatamente (hot-reload)
- **Compartilhamento de configuração**: Arquivo `.env` ou `config.json` do host
- **Logs**: Acessar logs gerados pelo container diretamente no host

### Sintaxe

```bash
docker container run -v <pasta-host>:<pasta-container> <imagem>
```

**Parâmetros:**

| Parâmetro | Descrição |
|-----------|-----------|
| `-v` | Flag para definir um volume (bind mount) |
| `<pasta-host>` | Caminho no host (ex: `$(pwd)/dados` ou `/home/user/dados`) |
| `<pasta-container>` | Caminho dentro do container (ex: `/app/dados`, `/usr/share`) |
| `<imagem>` | Imagem a ser utilizada |

**Exemplo:**

```bash
docker container run -v $(pwd)/teste:/usr/share alpine
```

- `$(pwd)/teste`: Mapeia pasta `teste` do diretório local para o container
- `/usr/share`: Diretório dentro do container onde os dados serão armazenados
- Qualquer arquivo criado em `/usr/share` dentro do container será salvo em `./teste` no host

### Exemplo Prático: Container Alpine com Volume

**Executar container interativo com volume**

```bash
docker container run -it --name alp1 -v $(pwd)/teste:/usr/share alpine
```

**Dentro do container:**

```bash
cd /usr/share
echo 'teste de volume no alpine' > teste.md
```

**No host (em outro terminal):**

```bash
ls teste/
cat teste/teste.md
```

**Resultado:** O arquivo `teste.md` criado dentro do container está disponível na pasta `teste/` do host.

### Verificar Volume em uma Imagem

Use `docker container inspect` para visualizar detalhes do mapeamento:

```bash
docker container inspect alp1
```

**Seção relevante da saída (campo `Mounts`):**

```json
"Mounts": [
  {
    "Type": "bind",
    "Source": "/home/plajiw/teste",
    "Destination": "/usr/share",
    "Mode": "",
    "RW": true,
    "Propagation": "rprivate"
  }
]
```

| Campo | Significado |
|-------|-------------|
| `Type` | Tipo de mount: `bind` (bind mount) ou `volume` (Docker volume) |
| `Source` | Caminho no host (`/home/plajiw/teste`) |
| `Destination` | Caminho no container (`/usr/share`) |
| `RW` | Read/Write — `true` permite leitura e escrita |
| `Propagation` | Política de propagação (`rprivate` = isolado) |

## Principais Usos de Volumes

| Caso de Uso | Descrição |
|-------------|-----------|
| **Persistência de dados** | Manter dados gerados pelo container após sua remoção |
| **Compartilhamento host↔container** | Acessar código-fonte, logs ou dados do host dentro do container |
| **Compartilhamento entre containers** | Múltiplos containers acessam o mesmo volume simultaneamente |
| **Banco de dados** | Persistir dados de aplicações de banco de dados (PostgreSQL, MySQL, Redis) |
| **Desenvolvimento** | Sincronizar código-fonte do host com o container para hot-reload |

## Volumes Docker (Docker Managed Volumes)

### Motivação

Volumes Docker diferem de bind mounts ao serem gerenciados totalmente pelo Docker: armazenados em local padronizado do host, não requerem caminho absoluto do desenvolvedor, e oferecem melhor desempenho e isolamento.

### Conceito

Um **Docker Volume** é um objeto de armazenamento nomeado, independente, gerenciado pelo Docker. Diferente de bind mount que aponta a um diretório arbitrário do host, volumes residem em caminho padrão (`/var/lib/docker/volumes/` no Linux) e são portáveis entre hosts.

### Criação de Volume

**Sintaxe:**

```bash
docker volume create <nome>
```

**Parâmetros:**

| Parâmetro | Descrição |
| --------- | --------- |
| `<nome>` | Nome do volume (obrigatório para referência posterior). Se omitido, Docker gera UUID aleatório |

**Exemplo prático:**

```bash
docker volume create dadosdb
docker volume ls
```

**Saída esperada:**

```text
DRIVER              VOLUME NAME
local               dadosdb
```

O volume `dadosdb` agora está pronto para ser utilizado por containers.

### Inspecionar Volume em uma Imagem

Antes de usar um volume, verificar se a imagem já tem pontos de mount predefinidos:

```bash
docker image pull mysql:5.7
docker image inspect mysql:5.7
```

**Procurar pela seção `Volumes`** na saída JSON:

```json
"Volumes": {
  "/var/lib/mysql": {}
}
```

Isso indica que a imagem MySQL foi construída para usar `/var/lib/mysql` como caminho onde armazena dados. Este é o local onde conectaremos nosso volume.

### Criar Container com Volume

**Sintaxe:**

```bash
docker container run -d --name <nome> -v <volume>:<caminho-container> -e <VARIÁVEL>=<valor> <imagem>
```

**Parâmetros:**

| Parâmetro | Descrição |
| --------- | --------- |
| `-d` | Executa em background (detached mode) |
| `--name` | Nome do container para referência posterior |
| `-v <volume>:<caminho>` | Monta volume nomeado em caminho específico do container |
| `-e <VAR>=<valor>` | Define variável de ambiente (nativa da imagem) |
| `<imagem>` | Imagem base para o container |

**Exemplo prático:**

```bash
docker container run -d --name mysql \
  -v dadosdb:/var/lib/mysql \
  -e MYSQL_ROOT_PASSWORD=senha123 \
  mysql:5.7
```

Isso:
- Cria container em background chamado `mysql`
- Monta volume `dadosdb` em `/var/lib/mysql` (local dos dados MySQL)
- Define senha root como `senha123`

### Verificar Status

```bash
docker container ls
```

Procurar pelo container `mysql` na lista. Se estiver rodando, status será `Up`.

### Acessar Container e Verificar Dados

**Sintaxe do `docker container exec`:**

```bash
docker container exec -it <container> <comando>
```

**Parâmetros:**

| Parâmetro | Descrição |
| --------- | --------- |
| `-i` (--interactive) | Mantém STDIN aberto mesmo desconectado; permite entrada de dados |
| `-t` (--tty) | Aloca pseudo-terminal (não é um terminal real, é virtualizado) |
| `-it` | Combinação de `-i` e `-t` para shell interativo completo |
| `<container>` | Nome ou ID do container |
| `<comando>` | Comando a executar no container (ex: `/bin/bash`, `mysql -u root -p`) |

**Lógica:**

- Sem `-i`, comando não pode receber entrada do teclado (útil para comandos únicos)
- Sem `-t`, não há prompt nem formatação de terminal
- Com `-it`, você obtém terminal completo dentro do container (acesso shell)

**Exemplo:**

```bash
docker container exec -it mysql /bin/bash
```

Isto abre shell Bash interativo dentro do container MySQL. Agora você está **dentro** do container, com acesso ao sistema de arquivos containerizado.

**Dentro do container, acessar MySQL:**

```bash
mysql -u root -p
# Digitar senha: senha123
```

**Operações SQL:**

```sql
SHOW DATABASES;
CREATE DATABASE testedb;
EXIT;
```

**Sair do container:**

```bash
exit
```

### Persistência: Remover e Recuperar Dados

A vantagem crítica de volumes: dados persistem mesmo após remoção do container.

**Parar e remover container:**

```bash
docker container stop mysql
docker container rm mysql
```

O volume `dadosdb` continua existindo no host com todos os dados intactos.

**Verificar volume ainda existe:**

```bash
docker volume ls
```

`dadosdb` aparece na lista.

### Reutilizar Volume em Novo Container

Criar novo container que monta o mesmo volume:

```bash
docker container run -d --name mysql2 \
  -v dadosdb:/var/lib/mysql \
  -e MYSQL_ROOT_PASSWORD=senha123 \
  mysql:5.7
```

**Verificar dados foram preservados:**

```bash
docker container exec -it mysql2 /bin/bash
```

Dentro do container:

```bash
mysql -u root -p
# Digitar senha: senha123
SHOW DATABASES;
# Resultado: verá `testedb` criada no container anterior!
EXIT;
exit
```

### Resumo: Ciclo Completo Volume Docker

| Etapa | Comando | Resultado |
| ----- | ------- | --------- |
| **1. Criar volume** | `docker volume create dadosdb` | Volume nomeado criado no host |
| **2. Criar container** | `docker run -v dadosdb:/var/lib/mysql mysql:5.7` | Container monta volume; dados vão para volume, não para container |
| **3. Inserir dados** | SQL dentro do container | Dados persistem no volume |
| **4. Parar container** | `docker container stop mysql` | Container para |
| **5. Remover container** | `docker container rm mysql` | Container deletado; volume sobrevive |
| **6. Novo container, mesmo volume** | `docker run -v dadosdb:/var/lib/mysql mysql:5.7` | Novo container acessa dados antigos |

### Inspecionar Detalhes do Volume

```bash
docker container inspect mysql
```

Procurar por seção `Mounts` para confirmar mapeamento:

```json
"Mounts": [
  {
    "Type": "volume",
    "Name": "dadosdb",
    "Source": "/var/lib/docker/volumes/dadosdb/_data",
    "Destination": "/var/lib/mysql",
    "Driver": "local",
    "RW": true
  }
]
```

| Campo | Significado |
| ----- | ----------- |
| `Type` | `volume` (Docker managed) vs `bind` (host path) |
| `Name` | Nome do volume |
| `Source` | Caminho físico no host (gerenciado por Docker) |
| `Destination` | Caminho dentro do container |
| `RW` | Read/Write — `true` permite leitura e escrita |

### Limpeza de Volumes Órfãos

Volumes não usados consumem espaço. Para listar e remover:

```bash
docker volume ls
docker volume rm <nome>
```

Cuidado: remover volume deleta seus dados permanentemente.

