suckless tools
==============

Este repositorio guarda minhas versoes locais de ferramentas suckless.
Tudo fica em subdiretorios simples, sem submodulos, para facilitar clonar,
compilar e instalar em outra maquina.

Ferramentas
-----------
- `dmenu`: menu dinamico para X.
- `dwm`: window manager dinamico para X.
- `keynav`: controle do mouse pelo teclado.
- `slstatus`: gerador de status para a barra do dwm.
- `slock`: bloqueador simples de tela X.
- `st`: terminal simples para X.

Dependencias Debian
-------------------
Para compilar e usar este conjunto em uma instalacao Debian limpa, instale pelo
menos:

    sudo apt install --no-install-recommends \
        build-essential \
        pkg-config \
        xorg \
        xinit \
        libx11-dev \
        libxft-dev \
        libxinerama-dev \
        libxrandr-dev \
        libxext-dev \
        libxrender-dev \
        libimlib2-dev \
        libcairo2-dev \
        libglib2.0-dev \
        libxtst-dev \
        xdotool \
        curl \
        python3 \
        python3-psutil \
        pipewire-jack \
        tmux \
        flameshot \
        gnome-screenshot \
        fonts-firacode \
        fonts-noto-core \
        fonts-noto-color-emoji \
        fonts-roboto

O que cada grupo cobre:

- `build-essential` e `pkg-config`: compilacao em C e descoberta de flags.
- `xorg` e `xinit`: servidor X e `startx`.
- `libx11-dev`, `libxft-dev`, `libxinerama-dev`, `libxrandr-dev`,
  `libxext-dev`, `libxrender-dev`: headers X usados por `dwm`, `dmenu`,
  `st`, `slock`, `slstatus` e `keynav`.
- `libimlib2-dev`: suporte a icone/PNG no `st`.
- `libcairo2-dev`: headers Cairo, incluindo `cairo-xlib.h`, usados pelo
  `keynav`.
- `libglib2.0-dev`: headers GLib usados pelo `keynav`.
- `libxtst-dev` e `xdotool`: dependencias ligadas ao controle de mouse/teclado
  do `keynav`.
- `curl`, `python3` e `python3-psutil`: scripts auxiliares do `slstatus`.
- `pipewire-jack`: inicia o Renoise integrado ao PipeWire.
- `tmux`: sessao aberta automaticamente pelo atalho de terminal do `dwm`.
- `flameshot` e `gnome-screenshot`: atalhos de captura de tela do `dwm`.
- `fonts-firacode`: fonte usada no `st`.
- `fonts-noto-core`, `fonts-noto-color-emoji` e `fonts-roboto`: fontes e
  simbolos usados pela barra do `dwm` e pelo `dmenu`.

Alguns itens exibidos na barra dependem de comandos pessoais que nao fazem
parte deste repositorio: `/usr/bin/psuinfo` e `/usr/local/bin/treino-show`.
Sem eles, o restante do ambiente continua funcionando, mas esses segmentos do
`slstatus` ficam vazios. Spotify, Fastpotify, Aseprite, Renoise, ChatGPT e
DwarFort tambem sao aplicativos opcionais chamados ou organizados pelo `dwm`.

Os dotfiles e servicos de sessao ficam em outro repositorio:

    git clone git@github.com:vtr88/dotfiles.git ~/Documentos/github/dotfiles

Como compilar
-------------
Entre no diretorio da ferramenta desejada e rode `make`:

    cd dwm
    make

O `keynav` nao e uma ferramenta suckless, mas fica neste repositorio porque
tambem faz parte do setup basico de uma maquina nova.

Como instalar
-------------
As ferramentas usam o alvo padrao dos projetos suckless. Para instalar em
`/usr/local`, rode dentro do diretorio da ferramenta:

    sudo make clean install

Configuracao
------------
Em geral, as customizacoes ficam em `config.h`. Quando existe `config.def.h`,
ele acompanha a mesma configuracao para manter a versao base documentada.

O fluxo normal e:

    editar config.h
    make
    sudo make clean install

Depois disso, reinicie o programa afetado. No caso do `dwm`, reinicie a sessao
X ou saia do dwm e rode `startx` de novo.

Arquivos gerados por build ficam fora do Git via `.gitignore`.
