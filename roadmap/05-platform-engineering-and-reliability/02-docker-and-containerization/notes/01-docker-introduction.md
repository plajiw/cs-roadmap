# Introdução ao Docker

Docker é uma plataforma para empacotar, distribuir e executar aplicações em containers. Seu objetivo central é garantir que o software rode de forma previsível em ambientes diferentes, como desenvolvimento local, homologação e produção, reduzindo problemas de compatibilidade e variações de infraestrutura.

No contexto de engenharia de software moderna, Docker é parte fundamental de práticas como DevOps, CI/CD, arquitetura de microsserviços e operações em nuvem.

## O que é um container

Um container é um padrão de unidade de software que empacota código e todas as suas dependências de uma aplicação fazendo que a mesma seja executada rapidamente de forma confiável de um ambiente computacional para outro. Ele inclui:

- Aplicação e seu código.
- Dependências (bibliotecas, runtimes e ferramentas necessárias).
- Configurações essenciais para execução.

Diferente de máquinas virtuais, containers não virtualizam hardware completo nem carregam um sistema operacional convidado inteiro. Em vez disso, compartilham o kernel do host e isolam processos por meio de mecanismos do sistema operacional (namespaces e cgroups no Linux). Isso torna containers mais leves, rápidos de iniciar e mais eficientes no uso de recursos.

## Docker no mercado

Em ambientes corporativos, Docker é amplamente adotado porque:

- Padroniza empacotamento e deploy entre times.
- Diminui o tempo de onboarding técnico.
- Facilita automação de pipelines de build, teste e entrega.
- Viabiliza arquitetura orientada a serviços com isolamento por processo.
- Integra naturalmente com orquestradores, especialmente Kubernetes.

Em resumo, Docker não substitui arquitetura, observabilidade ou segurança por si só, mas oferece uma base operacional consistente para essas práticas.

## Arquitetura do Docker

O ecossistema Docker pode ser entendido por seus componentes principais:

- **Docker Client:** interface de linha de comando (CLI) usada para enviar comandos, por exemplo `docker build`, `docker run`, `docker ps`.
- **Docker Engine (Daemon):** serviço responsável por construir imagens, criar containers, gerenciar redes e volumes.
- **Docker Registry:** repositório de imagens (Docker Hub, registries privados, GitHub Container Registry, Amazon ECR, etc.).
- **Docker Objects:** entidades gerenciadas pelo Engine (imagens, containers, redes, volumes e outros).

**Fluxo típico:**

1. O desenvolvedor cria uma definição de imagem em um Dockerfile.
2. O Docker Engine constrói uma imagem versionada.
3. A imagem é publicada em um registry.
4. Ambientes de execução puxam essa imagem e instanciam containers.

## Componentes essenciais

### Docker Image

Imagem é um artefato imutável que descreve o sistema de arquivos e metadados necessários para executar um container. Ela é composta em camadas, o que melhora cache de build e distribuição.

Pontos importantes:

- É um template de execução, não um processo em si.
- Deve ser versionada por tag e, quando necessário, por digest.
- Idealmente, deve ser pequena, determinística e segura.

### Docker Container

Container é a instância em execução de uma imagem. Ele adiciona uma camada de escrita sobre a imagem e executa um processo principal.

Características relevantes:

- Isolamento de processo, rede e sistema de arquivos.
- Ciclo de vida explícito: criar, iniciar, parar, remover.
- Efêmero por natureza; dados persistentes devem ir para volumes ou serviços externos.

### Dockerfile

Dockerfile é um arquivo declarativo com instruções para construir imagens. Cada instrução cria uma camada (com exceções em casos específicos de build otimizados).

Instruções comuns:

- `FROM`: define imagem base.
- `WORKDIR`: define diretório de trabalho.
- `COPY` e `ADD`: copia artefatos para a imagem.
- `RUN`: executa comandos durante o build.
- `ENV`: define variáveis de ambiente.
- `EXPOSE`: documenta porta usada pela aplicação.
- `CMD` e `ENTRYPOINT`: definem comando padrão de execução.

Exemplo:

```dockerfile
FROM python:3.12-alpine

WORKDIR /app

ENV PYTHONDONTWRITEBYTECODE=1
ENV PYTHONUNBUFFERED=1

COPY requirements.txt ./
RUN pip install --no-cache-dir -r requirements.txt

COPY . .

EXPOSE 5000
CMD ["python", "app.py"]
```

Leitura do exemplo:

1. Usa Python 3.12 em Alpine como base.
2. Define `/app` como diretório principal.
3. Ajusta variáveis para comportamento adequado em container.
4. Instala dependências.
5. Copia o código da aplicação.
6. Declara a porta 5000.
7. Define o comando padrão de inicialização.

### Docker Compose

Docker Compose permite descrever e executar aplicações multicontainer com um único arquivo YAML. É especialmente útil em desenvolvimento local e testes de integração.

Exemplo:

```yaml
services:
 web:
  build: .
  ports:
   - "5000:5000"
  depends_on:
   - redis

 redis:
  image: redis:7-alpine
```

Nesse caso, a aplicação `web` é construída localmente e integrada a um serviço `redis` pronto para uso.

## Recursos de suporte fundamentais

### Redes (Docker Networks)

Permitem comunicação entre containers e isolamento de tráfego. Redes bridge são comuns em ambiente local; em cenários distribuídos, o desenho de rede depende do orquestrador.

### Volumes

Volumes armazenam dados fora do ciclo de vida do container, garantindo persistência para bancos de dados, uploads e arquivos de estado.

### Variáveis de ambiente e segredos

Configuração sensível não deve ser embutida na imagem. Em ambiente profissional, segredos devem ser gerenciados por cofres dedicados (Vault, AWS Secrets Manager, Azure Key Vault, etc.).

## Diferença entre Docker e máquina virtual

- Máquina virtual: virtualiza hardware e executa sistema operacional completo.
- Container Docker: compartilha kernel do host e isola processos da aplicação.

Efeito prático:

- Containers iniciam mais rápido.
- Consomem menos recursos em média.
- A densidade de workloads por host tende a ser maior.

Por outro lado, isolamento de VM pode ser preferido em alguns cenários de segurança e compliance.

## Boas práticas profissionais

- Usar imagens base oficiais e minimais.
- Fixar versões de dependências para builds reproduzíveis.
- Evitar executar processos como root dentro do container.
- Reduzir superfície de ataque removendo ferramentas desnecessárias.
- Separar configuração por ambiente sem alterar a imagem.
- Tratar container como unidade descartável e observável (logs, métricas, traces).

## Limites do Docker

Docker resolve empacotamento e consistência de execução, mas não resolve sozinho:

- Orquestração em escala (réplicas, autoscaling, self-healing).
- Governança de segurança em nível organizacional.
- Observabilidade completa de sistemas distribuídos.
- Design de arquitetura e qualidade de código.

Por isso, no mercado, Docker costuma operar em conjunto com Kubernetes, ferramentas de CI/CD, scanners de vulnerabilidade, stacks de observabilidade e práticas de engenharia de confiabilidade.

## Síntese técnica

Docker é o padrão de fato para containerização no ciclo moderno de desenvolvimento e operação de software. Entender imagem, container, Dockerfile e Compose é requisito básico para atuar com plataformas em nuvem, pipelines de entrega e sistemas distribuídos de produção.
