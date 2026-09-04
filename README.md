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
- `surf`: navegador WebKitGTK minimo.
- `tabbed`: barra de abas XEmbed usada pelo `surf`.

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
        libgtk-3-dev \
        libgcr-3-dev \
        libwebkit2gtk-4.1-dev \
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
- `libgtk-3-dev`, `libgcr-3-dev` e `libwebkit2gtk-4.1-dev`: interface e motor
  web usados pelo `surf`.
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

Surf com abas
-------------
`surf` e `tabbed` sao programas separados. O `surf` implementa XEmbed e cada
janela dele vira uma aba dentro do `tabbed`.

Compile e instale os dois:

    cd tabbed
    make
    sudo make install

    cd ../surf
    make
    sudo make install

Para abrir uma URL na janela existente, ou criar a janela se ela ainda nao
existir:

    surf-open https://news.ycombinator.com/

Para iniciar ou focar a sessao pessoal:

    surf-session

No primeiro uso, o navegador abre uma unica pagina vazia. Depois disso, o
`surf-session` salva continuamente as abas abertas e sua ordem em
`~/.local/state/surf/session`, restaura a ultima sessao e ignora arquivos XID
obsoletos. Uma segunda chamada apenas reutiliza e foca a janela existente.
Tambem e possivel fornecer uma lista explicita de URLs ao `surf-session`.

Cookies, cache e dados locais ficam persistentes em `~/.surf`, portanto os
logins podem ser mantidos entre execucoes. O primeiro login e a compatibilidade
de cada site ainda dependem do WebKitGTK.

Downloads abrem em um `st`, sao gravados no diretorio configurado pelo sistema
como Downloads (com `~/Downloads` como fallback) e nunca sobrescrevem um arquivo
de mesmo nome: o `curl` cria os sufixos `.1`, `.2` e assim por diante.

Controles principais:

- `Ctrl-g`: abrir URLs ou pesquisar no DuckDuckGo pelo dmenu. A lista inclui
  os sites usuais e o historico local do que foi digitado.
- `Ctrl-t`: abrir uma aba vazia.
- `Ctrl-Shift-h` / `Ctrl-Shift-l`: trocar de aba.
- `Ctrl-1` ate `Ctrl-0`: ir diretamente para uma aba.
- `Ctrl-q`: fechar a aba atual.
- clique do meio em um link: abrir o link em uma nova aba.

O nivel de zoom e salvo por dominio em `~/.config/surf/zoom/`. `Ctrl-+` aumenta,
`Ctrl--` diminui e `Ctrl-Shift-q` volta a 100%; ao retornar ao mesmo dominio,
o ultimo nivel usado e reaplicado automaticamente.

Os bookmarks ficam em `~/.config/surf/bookmarks`, com uma URL por linha.
`Ctrl-Shift-1` ate `Ctrl-Shift-9` abrem as linhas 1 a 9 em uma nova aba;
`Ctrl-Shift-0` abre a linha 10. Linhas vazias e linhas iniciadas por `#` nao
abrem nada, mas continuam contando para a numeracao.

Os titulos curtos dos sites fixos ficam na tabela `urititles` em
`surf/config.h`. Sites que nao aparecem nessa tabela continuam usando o titulo
normal da pagina. O YouTube aparece sempre como `youtube`, em minusculas.

Os estilos pessoais do Stylus para Lichess e Last.fm ficam em `surf/styles/` e
sao aplicados automaticamente somente aos respectivos dominios. Na instalacao,
eles e a camada comum de avisos de cookies vao para
`/usr/local/share/surf/styles`.

A reducao dos avisos de cookies usa o CSS comum e o manipulador generico da
extensao instalada "I Still Don't Care About Cookies" 1.1.9. Isso cobre os
gerenciadores de consentimento mais comuns, mas nao inclui a grande lista de
regras especificas por site da WebExtension; portanto nao e garantia de cobrir
todo aviso existente. A procedencia e a licenca GPL ficam em
`surf/vendor/idcac/`.

Anuncios e rastreadores comuns sao bloqueados antes do download pelo filtro de
conteudo nativo do WebKitGTK, definido em `surf/filters/adblock.json`. A copia
compilada fica em `~/.cache/surf/content-filters/` e e renovada automaticamente
quando o arquivo instalado muda. A lista e deliberadamente conservadora para
nao comprometer logins, WhatsApp Web, Lichess ou reproducao no YouTube.

Os fontes foram importados diretamente dos repositorios oficiais. A revisao
exata de cada copia esta registrada em `surf/UPSTREAM` e `tabbed/UPSTREAM`.

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
