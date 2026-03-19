# Glossary  

Um glossário de termos e conceitos fundamentais para estudos em ciência da computação e engenharia de software.

---

## 📋 Índice

- [Segurança & Autenticação](#segurança--autenticação)
- [Arquitetura & Design](#arquitetura--design)
- [Padrões Arquitetônicos](#padrões-arquitetônicos)
- [Banco de Dados & Persistência](#banco-de-dados--persistência)
- [Sistemas & Infraestrutura](#sistemas--infraestrutura)
- [Redes & Comunicação](#redes--comunicação)
- [Testing & Qualidade](#testing--qualidade)
- [Desenvolvimento & Patterns](#desenvolvimento--patterns)

---

## Segurança & Autenticação

### MFA (Multi-Factor Authentication)

**Nível**: Intermediário  
**Definição**: Mecanismo de segurança que exige comprovação de identidade por meio de dois ou mais fatores independentes antes de conceder acesso a um sistema ou conta.

**Origem**: O conceito surgiu da necessidade de superar a fragilidade das senhas únicas. Ganhou força nos anos 1980–90 com sistemas bancários e militares, popularizando-se amplamente nos anos 2000 com a expansão dos serviços online.

**Explicação Técnica**: Os fatores de autenticação se dividem em três categorias clássicas:

- **Algo que você sabe**: senha, PIN, resposta secreta
- **Algo que você tem**: token físico, smartphone (TOTP via app como Google Authenticator, SMS), smart card
- **Algo que você é**: biometria (impressão digital, reconhecimento facial, iris)

A segurança do MFA reside na independência dos fatores — comprometer um não expõe os outros.

**Exemplos práticos**:

- Login no Gmail: senha + código TOTP do telefone
- Acesso bancário: cartão de crédito + biometria
- Autenticação SSH: chave privada + passphrase

**Relacionado**: 2FA, TOTP, FIDO2, WebAuthn, OAuth 2.0, JWT

**Referências**: NIST SP 800-63B (Digital Identity Guidelines)

---

### OAuth 2.0

**Nível**: Intermediário  
**Definição**: Protocolo de autorização aberto que permite que uma aplicação acesse recursos de um usuário em outro serviço, sem que o usuário compartilhe sua senha com a primeira aplicação.

**Origem**: Desenvolvido a partir de 2006 para resolver o problema de autorização delegada em ecossistemas de APIs. Padronizado como RFC 6749 em 2012. Amplamente adotado por Google, Facebook, Microsoft, GitHub.

**Explicação Técnica**: OAuth 2.0 resolve um problema clássico: como conceder permissão a uma aplicação sem compartilhar suas credenciais?

**Atores principais**:

- **Resource Owner**: Usuário que possui os recursos (seus dados)
- **Authorization Server**: Serviço que autentica o usuário e aprova a autorização
- **Client (Aplicação)**: Aplicação que quer acessar recursos em nome do usuário
- **Resource Server**: Serviço que mantém os recursos protegidos

**Grant Types** (formas de obter token de acesso):

1. **Authorization Code**: Mais seguro, padrão para web apps com backend
   - Aplicação redireciona usuário para Authorization Server
   - Usuário aprova
   - Authorization Server retorna código
   - Backend troca código por token (sem exposição ao cliente)

2. **Implicit**: Deprecated, antigo para Single Page Apps
   - Token retornado diretamente, sem código intermediário
   - Menos seguro, expõe token ao navegador

3. **Client Credentials**: Aplicação para aplicação, sem envolvimento de usuário
   - Usado em backend para backend
   - Aplicação se autentica com credenciais próprias

4. **Resource Owner Password Credentials**: Menos seguro, apenas para apps de confiança
   - Aplicação pede usuário/senha diretamente
   - Evitar sempre que possível

5. **Refresh Token**: Renovar token de acesso sem re-autenticar usuário
   - Access token curto (horas)
   - Refresh token longo (dias/meses)

**Importante**: OAuth 2.0 é sobre **autorização** (o que você pode fazer), não **autenticação** (quem você é). Para ambas, use **OpenID Connect** (camada de autenticação sobre OAuth 2.0).

**Exemplo de fluxo**: Login com Google em app. Redirecionado para Google. Aprova. Google retorna token. Seu app usa token para acessar email do usuário no Google.

**Relacionado**: OpenID Connect, JWT, SAML, SSO, Autenticação, Autorização, Access Control

---

### JWT (JSON Web Token)

**Nível**: Intermediário  
**Definição**: Padrão aberto (RFC 7519) para transmitir informações de forma compacta, assinada e verificável, frequentemente usado para autorização em APIs.

**Origem**: Proposto em 2010, padronizado em 2015. Rapidamente adotado em aplicações web modernas como alternativa a sessões baseadas em servidor.

**Explicação Técnica**: JWT consiste em três partes separadas por pontos (`.`):

1. **Header**: Tipo de token (JWT) e algoritmo de assinatura (HS256, RS256, ES256)
   - `{"alg": "HS256", "typ": "JWT"}`

2. **Payload**: Claims (declarações) sobre o usuário ou sessão
   - `{"sub": "1234567890", "name": "João", "iat": 1516239022}`
   - Claims comuns: `sub` (subject/user id), `iat` (issued at), `exp` (expiration), `aud` (audience)

3. **Signature**: Assinatura criptográfica que verifica integridade
   - Apenas servidor conhece a chave secreta
   - Token é **stateless**: servidor não precisa guardar nada

**Vantagens**:

- **Escalável**: Funciona bem em arquiteturas distribuídas (não precisa compartilhar sessão entre servidores)
- **APIs**: Padrão para autenticação em REST APIs e microserviços
- **Portável**: Funciona entre diferentes tecnologias e linguagens
- **Mobile-friendly**: Ideal para apps mobile e single page apps

**Limitações e Cuidados**:

- **Token revogado continua válido**: Difícil fazer logout imediato (precisa blacklist)
- **Payload não é encriptado**: Apenas codificado em base64. Dados sensíveis não devem estar aqui
- **Requer HTTPS**: Token pode ser interceptado se trafegar em HTTP plano
- **Expiração fixa**: Não pode ajustar TTL depois de emitido (daí refresh tokens)

**Ciclo de vida em aplicação web**:

1. Usuário faz login
2. Backend valida credenciais
3. Backend gera JWT (assinado com sua chave secreta)
4. Frontend armazena JWT (localStorage, sessionStorage, ou cookie httpOnly)
5. Em requisições subsequentes, frontend envia JWT em header: `Authorization: Bearer <token>`
6. Backend verifica assinatura e claims antes de processar requisição
7. Na expiração, usa refresh token para obter novo JWT

**Relacionado**: OAuth 2.0, OpenID Connect, Sessão, Bearer Token, Autenticação, Autorização

---

### CORS (Cross-Origin Resource Sharing)

**Nível**: Intermediário  
**Definição**: Mecanismo que permite que aplicações web façam requisições para servidores de domínios diferentes de forma controlada, contornando a política de Same-Origin do navegador.

**Origem**: Desenvolvido para resolver limitações de segurança impostas pelo navegador. Padronizado pelo W3C, agora gerenciado pelo WHATWG.

**Explicação Técnica**: **Same-Origin Policy** é restrição fundamental de navegadores: JavaScript de um domínio não pode acessar recursos de outro domínio (protocol, domain, port). Isso protege contra ataques, mas limita arquiteturas legítimas.

CORS permite que servidor declare explicitamente quais origens podem acessar seus recursos via headers HTTP:

- **Access-Control-Allow-Origin**: Quais domínios são permitidos
  - `https://app.example.com` (domínio específico)
  - `*` (qualquer domínio, menos seguro)

- **Access-Control-Allow-Methods**: Quais métodos HTTP (GET, POST, DELETE, PUT, PATCH)

- **Access-Control-Allow-Headers**: Quais headers customizados são aceitos (Authorization, Content-Type, etc.)

- **Access-Control-Allow-Credentials**: Se credenciais (cookies, auth headers) são permitidas

- **Access-Control-Max-Age**: Por quanto tempo browser cacheia resposta preflight

**Tipos de requisições**:

1. **Simples** (GET, POST, HEAD): Enviadas diretamente ao servidor. Servidor responde com headers CORS.

2. **Complex/Preflight** (DELETE, PUT, PATCH, custom headers): Primeiro faz requisição OPTIONS (preflight) para verificar permissões, depois faz requisição real.

**Cenário típico**:

- Frontend rodando em `https://app.example.com`
- API rodando em `https://api.example.com`
- Frontend faz requisição para API
- Navegador detecta origem diferente
- Envia preflight OPTIONS
- API responde com headers CORS permitindo a origem
- Navegador então permite a requisição real

**Comum em desenvolvimento**: Backend em `http://localhost:3000`, frontend em `http://localhost:3001`. Precisam se comunicar, logo precisa CORS.

**Relacionado**: Same-Origin Policy, HTTP Headers, Segurança de Navegador, REST API, Fetch API

---

### CSRF (Cross-Site Request Forgery)

**Nível**: Intermediário  
**Definição**: Vulnerabilidade de segurança onde um site malicioso força o navegador do usuário a fazer requisições não autorizadas em outro site onde o usuário está autenticado.

**Origem**: Vulnerabilidade conhecida há 20+ anos. Continua sendo uma das vulnerabilidades mais comuns em aplicações web.

**Explicação Técnica**: O ataque funciona assim:

1. Você está autenticado no seu banco (`bank.com`)
2. Você visita um site malicioso (`evil.com`) em outra aba
3. `evil.com` contém uma tag `<img src="bank.com/transferir?para=ataquante&valor=1000">`
4. Seu navegador envia requisição automática para o banco (com cookies de autenticação)
5. Transferência é feita sem seu consentimento explícito

**Por que funciona**: Navegador envia cookies automaticamente em requisições para o mesmo domínio, mesmo que a requisição venha de um site diferente.

**Proteção - CSRF Tokens**:

- Servidor gera token aleatório e envia ao cliente
- Cliente deve incluir token em cada requisição (POST, PUT, DELETE)
- Servidor valida token
- Assim, `evil.com` não consegue gerar token válido

**Outras proteções**:

- **SameSite Cookies**: Marca cookies para não serem enviadas em requisições cross-site
  - `Strict`: Nunca envia em cross-site
  - `Lax`: Envia apenas em GET navegacional
  - `None`: Envia em tudo (requer Secure flag)

- **Double Submit Cookies**: Token armazenado em cookie e enviado em header/body. Servidor valida se são iguais.

**Relacionado**: XSS, Segurança Web, Cookies, OWASP Top 10

---

### XSS (Cross-Site Scripting)

**Nível**: Intermediário  
**Definição**: Vulnerabilidade onde código JavaScript malicioso é injetado em página web e executado no navegador das vítimas.

**Origem**: Uma das vulnerabilidades mais antigas e comuns. Continua no OWASP Top 10.

**Explicação Técnica**: Três tipos principais:

1. **Stored XSS**: Código malicioso armazenado no servidor (banco de dados)
   - Atacante comenta em post com script: `<script>alert('hacked')</script>`
   - Comentário é armazenado no banco
   - Todos que visualizam o post executam o script
   - Mais perigoso

2. **Reflected XSS**: Código malicioso no URL
   - Atacante cria link: `www.site.com/search?q=<script>alert('hacked')</script>`
   - Compartilha link com vítimas
   - Vítima clica, código é executado
   - Requer interação da vítima

3. **DOM-based XSS**: Vulnerabilidade no JavaScript do cliente
   - JavaScript inseguro modifica DOM com dados não validados
   - Código malicioso é executado localmente

**Danos possíveis**:

- Roubar cookies/tokens (credenciais)
- Redirecionar usuário para site malicioso
- Modificar conteúdo da página
- Keylogging (capturar digitações)
- Comportamento malicioso em nome do usuário

**Proteção**:

- **Input Validation**: Validar tudo que vem de usuário
- **Output Encoding**: Codificar dados antes de renderizar (HTML escape)
- **Content Security Policy (CSP)**: Header HTTP que restringe quais scripts podem rodar
- **Usar frameworks seguros**: React, Angular escapam por padrão

**Relacionado**: CSRF, Segurança Web, OWASP Top 10, Input Validation

---

### SQL Injection

**Nível**: Intermediário  
**Definição**: Vulnerabilidade crítica onde código SQL malicioso é injetado em queries, comprometendo integridade e confidencialidade do banco de dados.

**Origem**: Uma das vulnerabilidades mais antigas e perigosas. Continua sendo muito comum.

**Explicação Técnica**: Ocorre quando aplicação constrói queries SQL concatenando strings diretamente com input do usuário.

**Exemplo inseguro**:

```sql
query = "SELECT * FROM users WHERE email = '" + userInput + "'"
```

Se `userInput` é `' OR '1'='1`, a query vira:

```sql
SELECT * FROM users WHERE email = '' OR '1'='1'
```

Retorna todos os usuários (a condição `'1'='1'` é sempre verdadeira).

**Possíveis ataques**:

- Retornar dados não autorizados
- Modificar ou deletar dados
- Escalar privilégios
- Executar operações administrativas

**Proteção - Prepared Statements** (melhor prática):

- Separar estrutura SQL de dados
- Servidor sabe onde estão dados vs estrutura
- Dados são escapados automaticamente
- Praticamente impossível injetar SQL

ORMs como Entity Framework também protegem (quando usado corretamente).

**Validação adicional**:

- Whitelist: Aceitar apenas valores conhecidos
- Input validation: Validar tipo e formato
- Least privilege: Usuário BD só tem permissões necessárias

**Relacionado**: Segurança Web, OWASP Top 10, Prepared Statements, ORM

---

## Arquitetura & Design

### Monolito

**Nível**: Iniciante  
**Definição**: Arquitetura de software onde toda aplicação é desenvolvida, implantada e executada como uma única unidade coesa, com componentes fortemente acoplados.

**Origem**: Padrão dominante até meados dos anos 2000. Surgiu naturalmente como forma de estruturar aplicações quando sistemas eram simples e equipes pequenas.

**Explicação Técnica**: Características principais:

- **Uma base de código única**: Todo o código reside em um repositório centralizado
- **Uma unidade de deploy**: Cada atualização requer rebuild e redeploy de toda aplicação
- **Acoplamento forte**: Componentes dependem uns dos outros diretamente
- **Banco de dados compartilhado**: Geralmente todas funcionalidades acessam mesmo banco
- **Escalabilidade horizontal limitada**: Escalas-se a aplicação inteira, não funcionalidades específicas
- **Inicialização rápida**: Simples de estruturar inicialmente, ótimo para MVPs

**Ciclo de vida típico**:

1. Começa simples (vantajoso)
2. Cresce e acumula complexidade
3. Acoplamento aumenta
4. Testes ficam lentos
5. Deploys ficam arriscados (qualquer mudança afeta tudo)
6. Mudanças têm efeitos em cascata inesperados
7. Equipes passam a se atrapalhar

**Quando é apropriado**:

- Aplicações pequenas a médias
- Equipes pequenas (até 5-8 pessoas)
- Domínio de negócio bem definido e estável
- Requisitos de latência ultra-baixa (evita chamadas de rede)
- MVP (Minimum Viable Product)

**Quando começa a ser problema**:

- Aplicação cresceu muito (>100k linhas)
- Equipe > 10 pessoas trabalhando no mesmo código
- Diferentes partes escalam independentemente (algumas partes recebem mais carga)
- Ciclos de deploy são longos e arriscados
- Dificuldade em usar diferentes tecnologias

**Relacionado**: Modular Monolith, Microservices, SOA, Acoplamento, Coesão

---

### Modular Monolith

**Nível**: Intermediário  
**Definição**: Evolução do monolito que mantém uma única unidade de deploy mas organiza o código em módulos independentes com interfaces claras e baixo acoplamento.

**Origem**: Reconhecimento de que nem sempre a separação física (microserviços) é a solução ideal. Surge como alternativa que oferece benefícios arquitetônicos de microserviços sem sua complexidade.

**Explicação Técnica**: Mantém a simplicidade operacional do monolito (uma unidade de deploy) mas com estrutura arquitetural de um sistema distribuído:

- **Módulos claros**: Cada domínio de negócio é um módulo (Pedidos, Pagamentos, Usuários, etc.)
- **Responsabilidades bem delimitadas**: Cada módulo sabe seu escopo
- **Dependências unidirecionais**: Módulos dependem de abstrações, não implementações concretas
- **Interfaces explícitas**: Cada módulo expõe contrato claro (o que fornece, o que requer)
- **Testes em isolamento**: Módulos podem ser testados independentemente
- **Deploy único**: Continua sendo uma unidade de deploy (por enquanto)

**Vantagem estratégica**: Organiza-se como se fosse microserviços. Se no futuro precisar separar um módulo em serviço próprio, mudanças são mínimas.

**Padrões de organização**:

- **Domain-driven**: Por domínio de negócio (Pedidos, Clientes, Inventário)
- **Layered**: Por camada técnica (Controllers, Services, Repositories) — menos recomendado
- **Híbrido**: Domínio + Camada

**Vs Monolito Tradicional**:

- Monolito tradicional: tudo junto, acoplado, difícil separar
- Modular Monolith: tudo junto, mas bem organizado, fácil separar depois

**Vs Microservices**:

- Microservices: múltiplas unidades de deploy, complexidade distribuída
- Modular Monolith: uma unidade de deploy, mas estrutura é preparada

**Quando usar**:

- Aplicação médio-grande com múltiplos domínios
- Equipe pequena-média
- Quer preparar o terreno para futuro crescimento
- Quer evitar complexidade prematura de microserviços

**Relacionado**: Monolito, Microservices, Acoplamento, Coesão, Modularização

---

### Microservices

**Nível**: Avançado  
**Definição**: Padrão arquitetural onde uma aplicação é construída como um conjunto de pequenos serviços independentes, cada um rodando em seu próprio processo e comunicando-se via APIs bem definidas.

**Origem**: Termo cunhado por James Lewis e Martin Fowler (2014), embora o padrão tenha evoluído de práticas de empresas como Amazon, Netflix e Uber nos anos 2000.

**Explicação Técnica**: Características fundamentais:

- **Decomposição por Domínio**: Cada serviço representa um contexto de negócio (Pedidos, Pagamentos, Inventário)
- **Independência de Implementação**: Cada serviço pode usar linguagem, banco de dados e framework diferentes
- **Unidades de Deploy Independentes**: Cada serviço é deployado separadamente
- **Escalabilidade Granular**: Serviços podem ser escalados horizontalmente de forma isolada
- **Falha Isolada**: Falha em um serviço não derruba toda aplicação (resiliência)
- **Ownership**: Equipes pequenas podem ser dona de um serviço end-to-end

**Comparação com Monólito**:

| Aspecto               | Monólito           | Microserviços               |
|-----------------------|--------------------|-----------------------------|
| Complexidade          | Simples inicial    | Complexa, distribuída       |
| Escalabilidade        | Monolítica         | Por serviço                 |
| Deploy                | Um artefato        | Múltiplos artefatos         |
| Banco de Dados        | Compartilhado      | Por serviço (preferência)   |
| Testing               | Integração difícil | Testes integração complexos |
| Latência              | Baixa (in-process) | Mais alta (rede)            |
| Operacional           | Simples            | Complexo                    |
| Independência de Time | Acoplado           | Independente                |

**Desafios reais**:

- **Distributed tracing e debugging**: Requisição passa por múltiplos serviços, difícil rastrear problema
- **Consistência de dados**: Sem transação global, usa eventual consistency
- **Network latency e falhas**: Rede é o novo ponto de falha (sempre falha)
- **Gerenciamento de versões de APIs**: Múltiplas versões de serviços rodando
- **Operacional**: Mais serviços = mais monitoramento, logging, alertas necessários
- **Overhead de orquestração**: Service mesh, circuit breakers, retry logic

**Quando é apropriado**:

- Aplicação grande e complexa
- Múltiplos domínios de negócio independentes
- Equipes pequenas e múltiplas (cada dona de um serviço)
- Diferentes partes precisam escalar independentemente
- Precisa usar diferentes tecnologias/linguagens

**Quando NÃO é apropriado**:

- Aplicação pequena-média
- Equipe pequena ou centralizada
- Domínio simples
- Latência ultra-crítica

**Relacionado**: Monolito, Modular Monolith, SOA, API Gateway, Service Mesh, Containerização, Kubernetes, Observabilidade

---

### SOA (Service-Oriented Architecture)

**Nível**: Avançado  
**Definição**: Paradigma arquitetural anterior aos microserviços, onde sistemas são decompostos em serviços reutilizáveis e independentes, frequentemente usando SOAP e ESBs.

**Origem**: Emergiu nos anos 2000 como resposta à complexidade crescente. Diferencia de microserviços por usar tecnologias mais pesadas (SOAP, ESBs) e focar em reuso.

**Explicação Técnica**: Componentes principais:

- **Enterprise Service Bus (ESB)**: Componente central que media comunicação entre serviços. Orquestra, transforma, roteia mensagens.
- **Serviços coarse-grained**: Serviços maiores, menos granulares que microserviços (diferença importante!)
- **SOAP e XML**: Protocolo de comunicação, contrastando com REST/JSON de microserviços
- **Reuso**: Foco em reutilizar serviços em múltiplos contextos

**Diferenças com Microservices**:

| Aspecto       | SOA              | Microserviços |
|---------------|------------------|---------------|
| Granularidade | Coarse-grained   | Fine-grained  |
| Comunicação   | SOAP, mensagens  | REST, async   |
| Orquestração  | ESB central      | Distribuída   |
| Reuso         | Altamente focado | Secundário    |
| Complexidade  | Operacional      | Arquitetural  |

**Problemas com SOA**:

- **ESB como ponto único de falha**: Tudo passa por ele, fica complexo
- **Overhead**: SOAP e XML são pesados
- **Acoplamento ao ESB**: Serviços dependem do ESB

**Legado**: SOA ainda existe em muitas empresas grandes, especialmente finanças. Microserviços evoluíram por aprender com limitações de SOA.

**Relacionado**: Microserviços, ESB, SOAP, REST, Integração

---

## Padrões Arquitetônicos

### MVC (Model-View-Controller)

**Nível**: Iniciante  
**Definição**: Padrão arquitetural que separa aplicação em três componentes: Model (dados/lógica), View (apresentação) e Controller (orquestração).

**Origem**: Descrito pela primeira vez em 1979 em SmallTalk. Tornou-se padrão em frameworks web (Rails, Django, ASP.NET).

**Explicação Técnica**:

- **Model**: Representa dados e lógica de negócio. Independente de como dados são apresentados.
- **View**: Apresentação dos dados ao usuário. HTML, templates, etc.
- **Controller**: Recebe requisições do usuário, manipula Model, decide qual View renderizar.

**Fluxo**: Usuário interage → Controller → Model → View → Resposta ao usuário.

**Vantagens**:

- Separação de responsabilidades
- Fácil de testar (Model independente)
- Reutilização de Views/Controllers

**Limitações**:

- Controller pode ficar inchado
- Comunicação bidirecionional entre componentes pode ficar complexa
- Model acoplado à aplicação

**Variações**: MVP (Model-View-Presenter), MVVM (Model-View-ViewModel), MVI (Model-View-Intent)

**Relacionado**: Arquitetura, Separação de Responsabilidades, MVP, MVVM, VIPER

---

### MVVM (Model-View-ViewModel)

**Nível**: Intermediário  
**Definição**: Padrão que separa lógica de apresentação (ViewModel) da View, facilitando binding bidirecional de dados e testabilidade.

**Origem**: Introduzido pela Microsoft em WPF (.NET). Popularizado em frameworks modernos como Vue.js, WPF, Xamarin.

**Explicação Técnica**:

- **Model**: Dados e lógica de negócio pura (igual ao MVC)
- **View**: UI, apenas apresentação. Não contém lógica.
- **ViewModel**: Contém lógica de apresentação, estado da tela, transformações de dados. Não conhece View.

**Diferença importante do MVC**: Binding bidirecional automático. Quando ViewModel muda, View atualiza automaticamente (e vice-versa).

**Benefícios**:

- ViewModel é testável sem referência à View
- Binding automático reduz código "plumbing"
- Separação clara entre lógica de apresentação e UI

**Quando usar**: Aplicações desktop (WPF, Xamarin) e SPAs com frameworks que suportam binding (Vue.js, Angular).

**Relacionado**: MVC, MVP, Data Binding, Apresentação

---

### DDD (Domain-Driven Design)

**Nível**: Avançado  
**Definição**: Abordagem de design de software que coloca o domínio de negócio no centro da arquitetura, usando linguagem ubíqua e conceitos para refletir realidade do negócio.

**Origem**: Popularizado por Eric Evans em livro homônimo (2003). Ganhou adoção massiva com microserviços (natural pairing).

**Explicação Técnica**: Conceitos principais:

- **Linguagem Ubíqua**: Vocabulário comum entre negócio e técnico. Desenvolvedores usam mesmos termos que domínio.
- **Bounded Context**: Limite explícito de aplicabilidade de um modelo. Diferentes contextos podem ter diferentes regras.
- **Aggregates**: Agrupamentos de entidades que formam unidade transacional coesa.
- **Value Objects**: Objetos que não têm identidade própria, só importa valor.
- **Repositories**: Abstração para persistência de agregados.
- **Services**: Lógica que não cabe em nenhuma entidade.

**Exemplo**: Sistema de e-commerce

- **Domínio Pedidos**: Pedido, Linha de Pedido, Status
- **Domínio Inventário**: Produto, Estoque, SKU
- Cada domínio tem sua linguagem ubíqua, suas regras

**Benefícios**:

- Código reflete realidade do negócio
- Facilita comunicação entre técnico e negócio
- Escalável para grandes sistemas
- Natural com microserviços

**Desafios**:

- Requer entendimento profundo do domínio
- Abstrações podem ser excessivas para domínios simples
- Curva de aprendizado

**Relacionado**: Arquitetura, Microserviços, Modularização, Bounded Context

---

### CQRS (Command Query Responsibility Segregation)

**Nível**: Avançado  
**Definição**: Padrão que separa lógica de escrita (Commands) da lógica de leitura (Queries), podendo ter modelos e bancos de dados diferentes para cada.

**Origem**: Padrão identificado por Greg Young em meados dos anos 2000. Ganhou popularidade com Event Sourcing e microserviços.

**Explicação Técnica**:

- **Commands**: Operações que mudam estado. Retornam sucesso/falha, não dados.
- **Queries**: Operações que leem dados. Nunca mudam estado.

**Separação de responsabilidades**: Normalmente em aplicações CRUD tradicionais, mesma entidade serve para leitura e escrita. CQRS separa:

- **Write Model**: Otimizado para escritas, validações, regras de negócio
- **Read Model**: Otimizado para leituras, denormalizado, pode estar em tecnologia diferente

**Exemplo**: Sistema de Pedidos

- **Write Model**: Valida pedido, verifica inventário, persiste (normalizado)
- **Read Model**: Denormalizado com dados agregados, desnormalizados para leitura rápida

**Benefícios**:

- Modelo de escrita pode ser complexo, modelo de leitura simples
- Escalabilidade diferente para leitura e escrita
- Possibilita Event Sourcing

**Desafios**:

- Sincronização entre modelos (eventual consistency)
- Complexidade aumentada
- Eventual consistency é difícil

**Variantes**: Frequentemente combinado com **Event Sourcing** (persistir mudanças como eventos).

**Relacionado**: Event Sourcing, DDD, Arquitetura, Escalabilidade

---

## Banco de Dados & Persistência

### ORM (Object-Relational Mapping)

**Nível**: Intermediário  
**Definição**: Técnica de mapeamento que translada dados entre tabelas de banco de dados relacional e objetos em linguagens de programação orientada a objetos.

**Origem**: Surgiu como forma de resolver impedance mismatch entre paradigma relacional (tabelas) e OOP (objetos). Populares desde anos 2000 (Hibernate, Entity Framework).

**Explicação Técnica**: ORM cria abstração entre código e banco:

```txt
Classe Usuario → Tabela users
Propriedade Name → Coluna name
Propriedade Email → Coluna email
```

Principais responsabilidades:

- **Mapeamento**: Classe → Tabela, propriedade → coluna
- **CRUD**: Geração de SQL para criar, ler, atualizar, deletar
- **Relacionamentos**: Mapeamento de relações (1:N, N:N)
- **Lazy Loading**: Carregamento sob demanda de dados relacionados
- **Tracking**: Detectar mudanças em objetos

**Vantagens**:

- Menos SQL para escrever manualmente
- Proteção contra SQL Injection
- Abstração de banco de dados (pode trocar bancos)
- Relacionamentos automáticos

**Limitações**:

- **N+1 Query Problem**: Código ineficiente gera muitas queries
- **Performance**: Queries geradas podem ser ineficientes
- **Complexidade**: Relacionamentos complexos ficam complicados
- **Debugging**: Difícil debugar SQL gerado

**ORMs populares**: Entity Framework (.NET), Hibernate (Java), SQLAlchemy (Python), Sequelize (Node.js).

**Quando usar**: Maioria dos casos, exceto queries muito complexas.

**Quando evitar**: Relatórios pesados, queries complexas com múltiplos joins. Considere usar SQL nativo.

**Relacionado**: Entity Framework, Banco de Dados, Persistência, N+1 Problem, Repository Pattern

---

### Entity Framework (EF)

**Nível**: Intermediário  
**Definição**: ORM moderno da Microsoft para .NET que abstrai banco de dados relacional em modelo orientado a objetos com LINQ.

**Origem**: Primeira versão lançada em 2008. Entity Framework Core (versão moderna) desde 2016. Padrão em aplicações .NET.

**Explicação Técnica**:

- **DbContext**: Classe que representa sessão com banco de dados. Coordena leitura/escrita.
- **DbSet<T\>**: Representa tabela no banco. Permite LINQ queries.
- **Migrations**: Versionamento de schema do banco.
- **Change Tracking**: Rastreia mudanças em objetos.
- **Relationships**: Suporte automático a relacionamentos.

**Abordagens**:

- **Code First**: Escreve classes C#, EF gera banco a partir delas (mais comum, mais controle)
- **Database First**: Banco já existe, EF gera classes a partir dele

**LINQ (Language Integrated Query)**: Permite escrever queries em C# que são traduzidas para SQL:

```csharp
var usuarios = dbContext.Users
    .Where(u => u.Email.Contains("@example.com"))
    .OrderBy(u => u.Name)
    .ToList(); // Aqui executa SQL no banco
```

**Benefícios em EF**:

- Tipo-seguro (compiler catches erros)
- IntelliSense
- Menos SQL manual
- Migrations automáticas

**Cuidados**:

- **N+1 Problem**: Fácil criar queries ineficientes
- **AsNoTracking()**: Desabilitar change tracking melhora performance se não vai modificar
- **Include/ThenInclude**: Eager loading de relacionamentos, evita lazy loading

**Relacionado**: ORM, LINQ, Banco de Dados, Migrations, Repository Pattern

---

### Repository Pattern

**Nível**: Intermediário  
**Definição**: Padrão de design que abstrai detalhes de persistência, fornecendo interface que trata coleção de entidades como uma coleção em memória.

**Origem**: Padrão clássico de design, popularizado em implementações com ORMs.

**Explicação Técnica**: Interface padronizada para persistência:

```csharp
IRepository<Produto>
  - Get(id)
  - GetAll()
  - Add(entidade)
  - Update(entidade)
  - Delete(id)
  - SaveChanges()
```

**Benefícios**:

- **Abstração**: Código de negócio não sabe de ORM/banco
- **Testabilidade**: Mock do repositório em testes
- **Flexibilidade**: Trocar banco de dados é fácil
- **Centralização**: Lógica de acesso em um lugar

**Cuidados**:

- **Sobre-abstração**: Às vezes é complexo demais
- **Leakage**: Detalhes de ORM vazam (ex: IQueryable)
- **Performance**: Abstração pode esconder queries ruins

**Complementos**:

- **Unit of Work**: Agrupa múltiplos repositórios em transação
- **Specification Pattern**: Encapsula critérios de busca complexos

**Relacionado**: ORM, Entity Framework, SOLID, Testabilidade, Unit of Work

---

### Migrations

**Nível**: Intermediário  
**Definição**: Versionamento controlado de mudanças no schema do banco de dados, permitindo evoluir estrutura de forma segura e rastreável.

**Origem**: Popularizadas em Rails com ActiveRecord Migrations. Adotadas em ORMs modernos (Entity Framework, Alembic).

**Explicação Técnica**: Cada migration é um arquivo versionado que descreve mudança no schema:

```sql
Migration: AddEmailToUsers
  Up: ALTER TABLE users ADD email VARCHAR(255)
  Down: ALTER TABLE users DROP COLUMN email
```

**Vantagens**:

- **Versionamento**: Historia completa de mudanças
- **Reprodutibilidade**: Qualquer dev pode aplicar migração localmente
- **Rollback**: Reverter mudanças se necessário
- **CI/CD**: Migrations podem rodar automaticamente no deployment

**Boas práticas**:

- Uma migration por mudança lógica
- Keep migrations simples
- Testar migrations (especialmente Down!)
- Cuidado com dados existentes

**Riscos**:

- Perdas de dados se migration errada
- Bloqueios no banco (migrations pesadas)
- Comunicação com DBA necessária em prod

**Relacionado**: Entity Framework, Banco de Dados, Versionamento, CI/CD

---

## Sistemas & Infraestrutura

### Bootstrap

**Nível**: Intermediário  
**Definição**: Etapa inicial de um sistema em que ele se prepara para funcionar de forma independente, executando sequência de inicialização autossuficiente.

**Origem**: Do inglês "pulling oneself up by one's bootstraps" (levantar-se puxando as próprias botas). Metáfora que representa inicializar algo sem recursos externos.

**Explicação Técnica**: Processo pelo qual computador ou sistema operacional inicia:

1. **Power-on**: Hardware Liga
2. **POST (Power-On Self Test)**: Testes de hardware (RAM, CPU, etc.)
3. **BIOS/UEFI**: Firmware que localiza bootloader
4. **Bootloader**: Pequeno programa que carrega kernel
5. **Kernel**: SO assume controle do hardware
6. **Driver Loading**: Inicializa drivers de periféricos
7. **File System**: Monta sistemas de arquivo
8. **User Space**: Disponibiliza serviços para aplicações

**Em aplicações**: Framework inicializa, carrega configurações, conecta ao banco, inicia servidor HTTP.

**Variantes**:

- **Cold Boot**: Ligação completa
- **Warm Boot**: Reinicialização de SO já rodando
- **Fast Boot**: Hibernação, retoma estado anterior

**Relacionado**: Kernel, BIOS, Bootloader, Firmware, Inicialização

---

### Kernel

**Nível**: Intermediário  
**Definição**: Núcleo central de um sistema operacional que gerencia recursos de hardware e media acesso de programas aos recursos do computador.

**Origem**: Termo adaptado da física/biologia. Popularizado em Unix/Linux.

**Explicação Técnica**: Responsabilidades principais:

- **Process Management**: Agendamento, criação, término de processos
- **Memory Management**: Alocação, proteção, virtual memory
- **I/O Management**: Controle de periféricos
- **File System**: Abstração de armazenamento
- **IPC (Inter-Process Communication)**: Mecanismos para processos se comunicarem
- **Interrupt Handling**: Responder a eventos de hardware

**Modos de operação**:

- **Kernel Mode**: Acesso irrestrito ao hardware
- **User Mode**: Acesso restrito, requer syscall para acessar kernel

**Arquiteturas**:

- **Monolítico** (Linux): Tudo em um espaço
- **Microkernel** (QNX): Mínimo em kernel, resto em user space
- **Híbrido** (Windows): Mistura dos dois

**Importante**: Transições entre modos têm custo (context switching).

**Relacionado**: Sistema Operacional, Process, Memory Management, Syscall

---

### Virtual Memory

**Nível**: Intermediário  
**Definição**: Técnica que permite programas utilizarem espaço de endereçamento maior que RAM física, usando disco como extensão.

**Origem**: Desenvolvida em mainframes na década de 1960. Padrão em SOs modernos.

**Explicação Técnica**: Divide memória em páginas (típicamente 4KB):

- **Page Table**: Mapa que traduz endereços virtuais em físicos
- **TLB (Translation Lookaside Buffer)**: Cache rápido para traduções frequentes
- **Page Replacement**: Algoritmos para decidir qual página descarregar (LRU, FIFO)
- **Swap Space**: Área do disco para páginas não em RAM

**Processo**:

1. Programa usa endereço virtual
2. MMU (Memory Management Unit) procura em TLB
3. Se hit, traduz direto
4. Se miss, procura em page table
5. Se página em RAM, traduz
6. Se página no disco (page fault), carrega de disco (lento!)

**Vantagens**:

- Programas ignoram limite de RAM
- Isolamento entre processos
- Multitarefa melhorada

**Desvantagens**:

- Page faults são caros (1000x mais lento)
- Thrashing: Muitas page faults, sistema fica lento

**Relacionado**: Memory Management, Paginação, Swap, Page Fault

---

## Redes & Comunicação

### TCP/IP

**Nível**: Intermediário  
**Definição**: Conjunto de protocolos que formam base da Internet, organizados em camadas, permitindo comunicação entre computadores.

**Origem**: Desenvolvido pelo ARPA nos anos 1970. Padronizado em 1983, tornou-se padrão da Internet.

**Explicação Técnica**: Pilha em camadas:

| Camada     | Protocolos                            | Função                |
|------------|---------------------------------------|-----------------------|
| Aplicação  | HTTP, HTTPS, DNS, SMTP, FTP, SSH, TLS | Serviços finais       |
| Transporte | TCP, UDP                              | Entrega ponto-a-ponto |
| Internet   | IP (IPv4, IPv6), ICMP                 | Roteamento            |
| Link       | Ethernet, WiFi                        | Transmissão física    |

**TCP vs UDP**:

- **TCP**: Confiável, ordenado, com handshake, mais overhead
- **UDP**: Sem garantias, rápido, menos overhead

**Modelo (simplificado) de comunicação**:

1. Cliente inicia conexão TCP (3-way handshake)
2. Cliente envia dados em pacotes
3. Servidor reconhece recebimento
4. Servidor envia resposta
5. Conexão fechada

**Importante**: TCP é responsabilidade de SO (kernel), não aplicação.

**Relacionado**: HTTP, DNS, Socket, Port, IP, IPv4, IPv6, Firewall

---

### DNS (Domain Name System)

**Nível**: Iniciante  
**Definição**: Sistema distribuído que traduz nomes de domínio legíveis em endereços IP que computadores usam para se comunicar.

**Origem**: Desenvolvido em 1983 por Paul Mockapetris. Substituiu arquivos HOSTS.txt, permitiu crescimento da Internet.

**Explicação Técnica**: Funciona como "agenda telefônica distribuída":

1. **Resolver local** (seu computador): Faz primeira requisição
2. **Recursive Resolver** (ISP normalmente): Procura iterativamente
3. **Root Nameserver**: Aponta para TLD server
4. **TLD Nameserver**: Aponta para authoritative server
5. **Authoritative Nameserver**: Retorna IP real

**Registros DNS**:

- **A**: IPv4
- **AAAA**: IPv6
- **CNAME**: Alias
- **MX**: Email servers
- **TXT**: Texto (SPF, DKIM, verificações)
- **NS**: Nameservers

**Caching**: Respostas cacheadas com TTL (Time To Live), reduzindo carga.

**Importante**: DNS é crítico. Se DNS falha, Internet inteira fica indisponível (ponto único de falha).

**Segurança**: DNSSEC valida respostas criptograficamente, DNS over HTTPS encripta queries.

**Relacionado**: HTTP, TCP/IP, IP Address, Domínios, Caching

---

## Testing & Qualidade

### Unit Testing

**Nível**: Intermediário  
**Definição**: Prática de testar unidades individuais de código (funções, métodos, classes) isoladamente de suas dependências.

**Origem**: Conceito antigo, popularizado em extrema programação e Test-Driven Development.

**Explicação Técnica**: Características de bom unit test:

- **Isolated**: Testa uma unidade, não múltiplas
- **Fast**: Executa em milissegundos
- **Independent**: Não depende de outros testes
- **Deterministic**: Sempre mesmo resultado

**Padrão AAA** (Arrange-Act-Assert):

1. **Arrange**: Preparar estado inicial
2. **Act**: Executar código que testa
3. **Assert**: Verificar resultado

**Mocks e Stubs**:

- **Mock**: Objeto fake que simula comportamento, permite verificar chamadas
- **Stub**: Objeto fake que retorna dados pré-configurados
- **Spy**: Como mock, mas também grava real behavior

**Vantagens**:

- Documentação executável
- Confiança para refatoração
- Detecção de bugs cedo

**Limitações**:

- Testa unidade isolada, não integração
- Mocks podem esconder comportamentos reais
- Custo de manutenção

**Frameworks**: xUnit, NUnit, Moq (C#), JUnit, Mockito (Java)

**Relacionado**: TDD, Integration Testing, Test Coverage, Mocks

---

### Integration Testing

**Nível**: Intermediário  
**Definição**: Testes que verificam interação entre múltiplos componentes (banco de dados, APIs, serviços).

**Origem**: Complemento necessário a unit tests. Crucial em microserviços.

**Explicação Técnica**: Diferenças com unit tests:

- **Escopo**: Múltiplos componentes
- **Velocidade**: Mais lentos (acessam disco, rede)
- **Setup**: Requerem ambiente real ou test double complexo
- **Cobertura**: Testa caminhos reais que unit tests não cobrem

**Tipos comuns**:

- Banco de dados real (test database)
- APIs reais (test server)
- Message queues
- File systems

**Exemplo**: Testa se método que salva usuário no banco realmente persiste e pode ser recuperado.

**Desafios**:

- Setup complexo
- Isolamento: Testes podem interferir uns nos outros
- Limpeza: Estado do banco após testes
- Velocidade: Executar suite inteira é lento

**Test Database**: Cópia do schema de produção, resetada entre testes.

**Relacionado**: Unit Testing, End-to-End Testing, Test Environment

---

### TDD (Test-Driven Development)

**Nível**: Intermediário  
**Definição**: Metodologia de desenvolvimento onde testes são escritos antes do código de produção (Red-Green-Refactor).

**Origem**: Popularizado em extreme programming. Defendido por Kent Beck, Robert Martin.

**Explicação Técnica**: Ciclo Red-Green-Refactor:

1. **Red**: Escrever teste que falha (funcionalidade não existe)
2. **Green**: Escrever código mínimo para passar no teste
3. **Refactor**: Melhorar código mantendo testes passando

**Benefícios**:

- Código é testável por design
- Documentação viva (testes documentam)
- Menos debug (falhas encontradas cedo)
- Confiança para mudanças

**Desvantagens**:

- Curva de aprendizado
- Mais tempo inicial (compensa depois)
- Não garante bom design
- Difícil em legacy code

**Boas práticas**:

- Comece simples
- Teste um comportamento por vez
- Não teste implementação, teste comportamento

**Relacionado**: Unit Testing, Qualidade, Design, Refactoring

---

## Desenvolvimento & Patterns

### SOLID Principles

**Nível**: Intermediário  
**Definição**: Conjunto de cinco princípios de design OOP que promovem código flexível, compreensível e mantível.

**Origem**: Conceitos compilados por Robert C. Martin (Uncle Bob) a partir de várias fontes.

**Explicação Técnica**:

**S - Single Responsibility Principle**:

- Uma classe tem uma e apenas uma razão para mudar
- Cada classe tem uma responsabilidade clara
- Benefício: Mudanças isoladas

**O - Open/Closed Principle**:

- Aberta para extensão, fechada para modificação
- Adicionar features sem mudar código existente
- Benefício: Menor risco em mudanças

**L - Liskov Substitution Principle**:

- Subclasse pode ser usada onde superclasse é esperada
- Comportamento não deve ser violado
- Benefício: Polimorfismo confiável

**I - Interface Segregation Principle**:

- Clientes não devem depender de interfaces que não usam
- Interfaces específicas ao invés de genéricas
- Benefício: Menos acoplamento

**D - Dependency Inversion Principle**:

- Dependa de abstrações, não de concretizações
- Alto nível não depende de baixo nível
- Ambos dependem de abstrações
- Benefício: Flexibilidade, testabilidade

**Benefícios gerais**:

- Código mais testável (dependency injection)
- Reduz acoplamento
- Facilita manutenção e extensão
- Código mais legível

**Armadilhas**:

- Sobre-engenharia para código simples
- Abstrações desnecessárias
- Obedecer SOLID não garante bom design

**Relacionado**: Design Patterns, Clean Code, Refactoring, OOP

---

### Design Patterns

**Nível**: Intermediário  
**Definição**: Soluções reutilizáveis para problemas comuns em design de software, documentadas e testadas em diferentes contextos.

**Origem**: "Gang of Four" (Gamma, Helm, Johnson, Vlissides) em livro "Design Patterns" (1994). Adaptado de padrões arquitetônicos.

**Explicação Técnica**: Três categorias principais:

**Padrões Criacionais** (como criar objetos):

- **Singleton**: Uma única instância de classe em toda aplicação
- **Factory**: Criar objetos sem especificar classes concretas
- **Builder**: Construir objetos complexos passo a passo
- **Prototype**: Clonar objetos existentes

**Padrões Estruturais** (como organizar classes e objetos):

- **Adapter**: Interface compatível para classes incompatíveis
- **Decorator**: Adicionar responsabilidades dinamicamente
- **Facade**: Interface simplificada para subsistema complexo
- **Proxy**: Substituto/placeholder para outro objeto

**Padrões Comportamentais** (como objetos interagem):

- **Observer**: Notificação automática de mudanças
- **Strategy**: Algoritmos intercambiáveis
- **Command**: Encapsular requisição como objeto
- **State**: Comportamento muda conforme estado

**Importante**: Padrões não são soluções universais. Use quando apropriado, não forçadamente.

**Riscos**:

- Sobre-engenharia
- Padrão errado para problema
- Complexidade desnecessária

**Relacionado**: SOLID, Clean Code, Refactoring, Arquitetura

---

### Dependency Injection (DI)

**Nível**: Intermediário  
**Definição**: Padrão de design que reduz acoplamento fornecendo dependências a um objeto ao invés dele criar as próprias.

**Origem**: Padrão fundamental em frameworks modernos (Spring, .NET Core, etc.).

**Explicação Técnica**: Problemas sem DI:

```txt
Classe OrderService criar suas próprias dependências
OrderService → cria EmailService
OrderService → cria PaymentService
Se EmailService muda, OrderService quebra
Difícil testar (não consegue usar mock)
```

Com DI:

```txt
OrderService recebe suas dependências injetadas
OrderService(emailService, paymentService)
Dependências podem ser reais ou mocks
Fácil testar
```

**Tipos de Injeção**:

1. **Constructor Injection**: Via construtor (preferida)
2. **Property Injection**: Via propriedade
3. **Method Injection**: Via parâmetro de método

**DI Containers**: Frameworks que gerenciam injeção automaticamente (Autofac, Unity, built-in em .NET Core).

**Vantagens**:

- Reduz acoplamento
- Facilita testes (mocks)
- Código mais flexível
- Inversão de controle

**Armadilhas**:

- Complexidade em excesso
- Debugging difícil (código espalhado)
- Constructor muito cheio (code smell)

**Relacionado**: SOLID (especialmente D), Inversion of Control, Testabilidade

---

### Design Anti-patterns (Code Smells)

**Nível**: Intermediário  
**Definição**: Padrões de design problemáticos que indicam código fraco, difícil de manter ou com potencial para bugs.

**Origem**: Popularizados por Kent Beck e Martin Fowler em "Refactoring" (1999).

**Explicação Técnica**: Exemplos comuns:

**God Object**: Uma classe faz tudo, tem muitas responsabilidades

- Sintoma: Classe com 1000+ linhas, muitos métodos
- Solução: Quebrar em classes menores (SRP)

**Tight Coupling**: Classes fortemente dependentes

- Sintoma: Mudança em uma quebra muitas outras
- Solução: Interfaces, DI, abstrações

**Feature Envy**: Classe usa muitos métodos de outra classe

- Sintoma: `obj.X, obj.Y, obj.Z` repetido
- Solução: Mover lógica para a classe que "possui" os dados

**Duplicate Code**: Mesmo código em múltiplos lugares

- Sintoma: Copy-paste de lógica
- Solução: Extrair em método/classe (Don't Repeat Yourself - DRY)

**Dead Code**: Código não usado

- Sintoma: Métodos/classes nunca chamados
- Solução: Deletar (version control permite recuperar)

**Magic Numbers**: Valores hardcoded sem significado

- Sintoma: `if (age > 18)` sem explicação
- Solução: Usar constantes nomeadas

**Importance**: Code smells não são bugs, mas indicadores de problemas. Nem sempre requerem mudança imediata.

**Relacionado**: Refactoring, Clean Code, Code Review, Manutenibilidade

---

### Refactoring

**Nível**: Intermediário  
**Definição**: Processo de melhorar código sem alterar seu comportamento externo, removendo code smells e melhorando design.

**Origem**: Popularizado por Martin Fowler em livro "Refactoring" (1999).

**Explicação Técnica**: Refatorações comuns:

- **Extract Method**: Código duplicado → novo método
- **Extract Class**: Classe grande → múltiplas classes
- **Replace Magic Number**: Constante nomeada
- **Rename**: Nomes mais claros
- **Move Method**: Método para classe mais apropriada
- **Introduce Parameter Object**: Múltiplos parâmetros → objeto

**Processo seguro**:

1. Testes em verde (todos passam)
2. Pequenas mudanças
3. Rodar testes frequentemente
4. Verificar diff antes de commit

**Importância**: Refactoring contínuo mantém código saudável. Adiar accumula complexidade.

**Risco**: Sem testes, refactoring é perigoso. Testes garantem que comportamento não muda.

**Relacionado**: Testing, Design Patterns, Code Smells, Clean Code

---

## 📌 Padrão de Registro

Cada termo no glossário segue estrutura:

```markdown
### [Termo]

**Nível**: [Iniciante | Intermediário | Avançado]
**Definição**: [Uma linha, concisa]

**Origem**: [Histórico/contexto]

**Explicação Técnica**: [Detalhamento aprofundado]

**Relacionado**: [Termos vinculados]

**Referências**: [Links/citações opcionais]
```
