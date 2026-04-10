
- No passado era comum haver diversos servidores locais para executar diferentes funções

Apache Microsoft ISS Banco de Dados

Alto custo de manutenção de hardware, software, rede
Grande ociosidade operacional, difícil mencionar cada máquina para otimziar os recursos máximo, maquinas com picos curtos de uso e longos momentos de ociosidade
Baixa escalabilidade
Dificil manutenção

Máquinas Vitruasl virtualização
Ataves do Hypervisor que trabalha a cima do sistema operacional, emulando o hardfisico dentro da máquina virtual
Implantar as aplicações, permitindo criar diversa máquinas irtuais e aplicações
aproveitando os recursos e reduzindo as ociosidade, baixo custo de hardware e melhor 
aproveitamento e gerenciamento de software

Problemas da virtualização
- nbecessidade de baixar o sistema de operacional em cada máquina virtual, dependo poderia ser difernete
Cuistos de manutenção e configuraçao do SO
Manter muitos SO gasta muito tempo

Para contornar isso surgiu a tecnologia de container
capacidade de empacotar um aplicação comt doas suas dpeendencais em uma nidade padronizada para desenovvimento de software, sem rpecisar de máquina virtual, sistema operacional

Nos container satuam diretamente no sistema oepracional, comatilahndo os recursos do kernel com o host
Divide o mesmo SO
Compartilha recursos do Kernal (I/O, mem´roai, rede, etc)

Necessidade dos containers

nems empre é viável baixar em um unico sistema operacional ou ter problemas no gereniamnto de recursos como portas
memoria e dificuldade de gerenciar, é dificil isolar as aplicações. Esse é o papel do conteinaer
essa

Problemas de gerenciamento de utuilziado de recurusos como portas de rede

Necessidade de versão específica de uma linguagem

Dificil isolar as paicações para evitar conflitos

Aqui temos o Docker -> criação, comparilhamento e gerenciamento de container

## Apresentação do Docker

Principal benefício do Coker é que ele permite que os usuarios empacorem m aplicativo com todas as suas dependcias em um unidade padronizada (container) para desenvoleimtno de software que poderá ser exetado ema mbvientes distinyos

para o docker container é um espaço reservado na memória que é ececutato na memoria que é inpedemnte e isolado de outros containers ou do proprio host

é uma tecnologia de virtualização de ambientes, como máquinas virtuais

Diferenaca entre o container é no docker é comptado o kernel com o sistema operacional do host

isso faz com que o desemenpi aumenteo e o consumo de memoria no container diminua

menos consumo de espaço físico

overhead mínimo possível

Para poder ser ecuitado im container possui asscoaidao a ele um sistema de arquivos completo e isolado que contem as dependencias e bibliotecas necessarios
Este sistema de arquivos somenteleitura ~sao conhecidas como imagem e aprtie delas é criada os container
é a represnetao estática da aplicação e sas configiação, o contienr a execução na memoria do host