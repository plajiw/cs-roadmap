# Introducao ao Docker

Docker e uma plataforma para empacotar, distribuir e executar aplicacoes em containers. Seu objetivo central e garantir que o software rode de forma previsivel em ambientes diferentes, como desenvolvimento local, homologacao e producao, reduzindo problemas de compatibilidade e variacoes de infraestrutura.

No contexto de engenharia de software moderna, Docker e parte fundamental de praticas como DevOps, CI/CD, arquitetura de microsservicos e operacoes em nuvem.

## O que e um container

Um container é um padrão de unidade de software que empacota código e todas as suas dependências de uma aplicação fazendo que a mesma seja executada rapidamente de forma confiável de um ambiente computacional para outro. Ele inclui:

- Aplicacao e seu codigo.
- Dependencias (bibliotecas, runtimes e ferramentas necessarias).
- Configuracoes essenciais para execucao.

Diferente de maquinas virtuais, containers nao virtualizam hardware completo nem carregam um sistema operacional convidado inteiro. Em vez disso, compartilham o kernel do host e isolam processos por meio de mecanismos do sistema operacional (namespaces e cgroups no Linux). Isso torna containers mais leves, rapidos de iniciar e mais eficientes no uso de recursos.

## Docker no mercado

Em ambientes corporativos, Docker e amplamente adotado porque:

- Padroniza empacotamento e deploy entre times.
- Diminui o tempo de onboarding tecnico.
- Facilita automacao de pipelines de build, teste e entrega.
- Viabiliza arquitetura orientada a servicos com isolamento por processo.
- Integra naturalmente com orquestradores, especialmente Kubernetes.

Em resumo, Docker nao substitui arquitetura, observabilidade ou seguranca por si so, mas oferece uma base operacional consistente para essas praticas.

## Arquitetura do Docker

O ecossistema Docker pode ser entendido por seus componentes principais:

- Docker Client: interface de linha de comando (CLI) usada para enviar comandos, por exemplo `docker build`, `docker run`, `docker ps`.
- Docker Engine (Daemon): servico responsavel por construir imagens, criar containers, gerenciar redes e volumes.
- Docker Registry: repositorio de imagens (Docker Hub, registries privados, GitHub Container Registry, Amazon ECR, etc.).
- Docker Objects: entidades gerenciadas pelo Engine (imagens, containers, redes, volumes e outros).

Fluxo tipico:

1. O desenvolvedor cria uma definicao de imagem em um Dockerfile.
2. O Docker Engine constroi uma imagem versionada.
3. A imagem e publicada em um registry.
4. Ambientes de execucao puxam essa imagem e instanciam containers.

## Componentes essenciais

### Docker Image

Imagem e um artefato imutavel que descreve o sistema de arquivos e metadados necessarios para executar um container. Ela e composta em camadas, o que melhora cache de build e distribuicao.

Pontos importantes:

- E um template de execucao, nao um processo em si.
- Deve ser versionada por tag e, quando necessario, por digest.
- Idealmente, deve ser pequena, deterministica e segura.

### Docker Container

Container e a instancia em execucao de uma imagem. Ele adiciona uma camada de escrita sobre a imagem e executa um processo principal.

Caracteristicas relevantes:

- Isolamento de processo, rede e sistema de arquivos.
- Ciclo de vida explicito: criar, iniciar, parar, remover.
- Efemero por natureza; dados persistentes devem ir para volumes ou servicos externos.

### Dockerfile

Dockerfile e um arquivo declarativo com instrucoes para construir imagens. Cada instrucao cria uma camada (com excecoes em casos especificos de build otimizados).

Instrucoes comuns:

- `FROM`: define imagem base.
- `WORKDIR`: define diretorio de trabalho.
- `COPY` e `ADD`: copia artefatos para a imagem.
- `RUN`: executa comandos durante o build.
- `ENV`: define variaveis de ambiente.
- `EXPOSE`: documenta porta usada pela aplicacao.
- `CMD` e `ENTRYPOINT`: definem comando padrao de execucao.

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
2. Define `/app` como diretorio principal.
3. Ajusta variaveis para comportamento adequado em container.
4. Instala dependencias.
5. Copia o codigo da aplicacao.
6. Declara a porta 5000.
7. Define o comando padrao de inicializacao.

### Docker Compose

Docker Compose permite descrever e executar aplicacoes multicontainer com um unico arquivo YAML. E especialmente util em desenvolvimento local e testes de integracao.

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

Nesse caso, a aplicacao `web` e construida localmente e integrada a um servico `redis` pronto para uso.

## Recursos de suporte fundamentais

### Redes (Docker Networks)

Permitem comunicacao entre containers e isolamento de trafego. Redes bridge sao comuns em ambiente local; em cenarios distribuidos, o desenho de rede depende do orquestrador.

### Volumes

Volumes armazenam dados fora do ciclo de vida do container, garantindo persistencia para bancos de dados, uploads e arquivos de estado.

### Variaveis de ambiente e segredos

Configuracao sensivel nao deve ser embutida na imagem. Em ambiente profissional, segredos devem ser gerenciados por cofres dedicados (Vault, AWS Secrets Manager, Azure Key Vault, etc.).

## Diferenca entre Docker e maquina virtual

- Maquina virtual: virtualiza hardware e executa sistema operacional completo.
- Container Docker: compartilha kernel do host e isola processos da aplicacao.

Efeito pratico:

- Containers iniciam mais rapido.
- Consomem menos recursos em media.
- A densidade de workloads por host tende a ser maior.

Por outro lado, isolamento de VM pode ser preferido em alguns cenarios de seguranca e compliance.

## Boas praticas profissionais

- Usar imagens base oficiais e minimais.
- Fixar versoes de dependencias para builds reprodutiveis.
- Evitar executar processos como root dentro do container.
- Reduzir superficie de ataque removendo ferramentas desnecessarias.
- Separar configuracao por ambiente sem alterar a imagem.
- Tratar container como unidade descartavel e observavel (logs, metricas, traces).

## Limites do Docker

Docker resolve empacotamento e consistencia de execucao, mas nao resolve sozinho:

- Orquestracao em escala (replicas, autoscaling, self-healing).
- Governanca de seguranca em nivel organizacional.
- Observabilidade completa de sistemas distribuidos.
- Design de arquitetura e qualidade de codigo.

Por isso, no mercado, Docker costuma operar em conjunto com Kubernetes, ferramentas de CI/CD, scanners de vulnerabilidade, stacks de observabilidade e praticas de engenharia de confiabilidade.

## Sintese tecnica

Docker e o padrao de fato para containerizacao no ciclo moderno de desenvolvimento e operacao de software. Entender imagem, container, Dockerfile e Compose e requisito basico para atuar com plataformas em nuvem, pipelines de entrega e sistemas distribuidos de producao.
