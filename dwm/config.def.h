/* See LICENSE file for copyright and license details. */

/*
 * Aparencia geral.
 *
 * borderpx continua em 1 para manter a separacao visual minima entre janelas.
 * O foco nao usa borda verde; a borda selecionada foi escurecida no esquema
 * de cores para preservar o espacamento sem chamar atencao.
 */
static const unsigned int borderpx  = 1;
static const unsigned int snap      = 32;
/* Systray embutida no dwm: substitui stalonetray/tint2 para icones de bandeja. */
static const unsigned int systraypinning = 0;
static const unsigned int systrayonleft = 0;
static const unsigned int systrayspacing = 2;
static const int systraypinningfailfirst = 1;
static const int showsystray        = 1;
/* Barra embaixo para ficar no mesmo lugar onde o tint2 ficava. */
static const int showbar            = 1;
static const int topbar             = 0;
/* Fonte mais pesada para legibilidade e fallback para emoji/glyphs do status. */
static const char *fonts[]          = { "Noto Sans:style=Bold:size=10", "Noto Color Emoji:size=10" };
static const char dmenufont[]       = "Roboto:size=9";
static const char col_gray1[]       = "#2e2821";
static const char col_gray2[]       = "#4b4d3b";
static const char col_gray3[]       = "#bdca58";
static const char col_gray4[]       = "#fbf1c7";
static const char col_orange[]      = "#ff9f3f";
static const char col_selectedbg[]  = "#241f1a";
static const char col_statusbg[]    = "#2e2821";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	/* A tag selecionada ganha apenas um marrom mais profundo. */
	[SchemeSel]  = { col_gray3, col_selectedbg, col_selectedbg },
	/* O slstatus e o restante da barra compartilham a mesma base marrom. */
	[SchemeStatus] = { col_gray3, col_statusbg, col_statusbg },
	/* Numeros laranja; nomes dos aplicativos continuam verdes. */
	[SchemeTagNum] = { col_orange, col_gray1, col_gray2 },
	[SchemeTagNumSel] = { col_orange, col_selectedbg, col_selectedbg },
};

/*
 * Tags fixas usadas como "areas de trabalho".
 * Os nomes dos apps sao adicionados dinamicamente pelo patch local em dwm.c.
 */
static const char *tags[] = { "1", "2", "3", "4", "5", "6" };

/*
 * Regras de abertura.
 *
 * tags mask: tag inicial do app.
 * isfloating: janela flutuante, quando o app se comporta melhor assim.
 * isfullscreen: extensao local para abrir em fullscreen automaticamente.
 */
static const Rule rules[] = {
	/* class          instance       title       tags mask     isfloating   isfullscreen monitor */
	{ "st-256color",  NULL,          NULL,       1 << 0,       0,           0,           -1 },
	{ "St",           NULL,          NULL,       1 << 0,       0,           0,           -1 },
	{ "URxvt",        NULL,          NULL,       1 << 0,       0,           0,           -1 },
	{ "Alacritty",    NULL,          NULL,       1 << 0,       0,           0,           -1 },
	{ "firefox-esr",  NULL,          NULL,       1 << 1,       0,           0,           -1 },
	{ "Spotify",      NULL,          NULL,       1 << 2,       1,           0,           -1 },
	{ "Aseprite",     NULL,          NULL,       1 << 3,       0,           0,           -1 },
	{ "tiled",        NULL,          NULL,       1 << 3,       1,           0,           -1 },
	{ "Renoise",      NULL,          NULL,       1 << 4,       0,           0,           -1 },
	{ "Code",         NULL,          NULL,       1 << 5,       0,           0,           -1 },
	{ "VSCodium",     NULL,          NULL,       1 << 5,       0,           0,           -1 },
	{ "mpv",          NULL,          NULL,       0,            1,           0,           -1 },
	{ "Gimp",         NULL,          NULL,       0,            1,           0,           -1 },
};

/*
 * Layouts.
 *
 * Monocle vem primeiro porque este setup trata cada tag como uma tela cheia
 * propria. Floating fica disponivel para apps como Spotify e janelas que
 * precisam escapar do tiling.
 */
static const float mfact     = 0.55;
static const int nmaster     = 1;
static const int resizehints = 0;
static const int lockfullscreen = 1;
static const int refreshrate = 120;

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[M]",      monocle },
	{ "><>",      NULL },
	{ "[]=",      tile },
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALTKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* Comandos chamados pelos atalhos. Mantem caminhos explicitos para os builds em /usr/local. */
static char dmenumon[2] = "0";
static const char *dmenucmd[]     = { "/usr/local/bin/dmenu_run", "-i", "-m", dmenumon, NULL };
static const char *termcmd[]      = { "/usr/local/bin/st", "-e", "tmux", NULL };
static const char *firefoxcmd[]   = { "firefox-esr", NULL };
static const char *spotifycmd[]   = { "/usr/bin/spotify", NULL };
static const char *asepritecmd[]  = { "/usr/bin/aseprite", NULL };
static const char *renoisecmd[]   = { "pw-jack", "renoise", NULL };
static const char *lockcmd[]      = { "/usr/local/bin/slock", "/usr/bin/systemctl", "suspend", NULL };
static const char *screenshotcmd[]= { "flameshot", "gui", NULL };
static const char *gnomeshotcmd[] = { "gnome-screenshot", "-i", NULL };
static const char *greekcmd[]     = { "/home/soth/.config/greek.sh", NULL };

static unsigned int
tagindex(unsigned int tagset)
{
	unsigned int i;

	for (i = 0; i < LENGTH(tags); i++)
		if (tagset & (1 << i))
			return i;
	return 0;
}

static void
viewrel(const Arg *arg)
{
	/* Navegacao relativa entre tags, equivalente ao fluxo antigo de desktops. */
	int i = tagindex(selmon->tagset[selmon->seltags]);
	int next = i + arg->i;

	if (next < 0)
		next = 0;
	if (next >= LENGTH(tags))
		next = LENGTH(tags) - 1;
	if (next != i)
		view(&(Arg){.ui = 1 << next});
}

static void
tagrel(const Arg *arg)
{
	/* Move a janela atual para a tag anterior/proxima sem precisar escolher numero. */
	int i, next;

	if (!selmon->sel)
		return;
	i = tagindex(selmon->sel->tags);
	next = i + arg->i;
	if (next < 0)
		next = 0;
	if (next >= LENGTH(tags))
		next = LENGTH(tags) - 1;
	if (next != i)
		tag(&(Arg){.ui = 1 << next});
}

static void
lowerclient(const Arg *arg)
{
	/* Aproxima o comportamento de Alt-Escape: abaixa a janela e foca a proxima. */
	if (!selmon->sel)
		return;
	XLowerWindow(dpy, selmon->sel->win);
	focusstack(&(Arg){.i = +1});
}

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ ALTKEY,                       XK_1,      spawn,          {.v = dmenucmd } },
	{ ALTKEY,                       XK_2,      spawn,          {.v = termcmd } },
	{ ALTKEY,                       XK_3,      spawn,          {.v = firefoxcmd } },
	{ ALTKEY,                       XK_4,      spawn,          {.v = spotifycmd } },
	{ ALTKEY,                       XK_5,      spawn,          {.v = asepritecmd } },
	{ ALTKEY,                       XK_6,      spawn,          {.v = renoisecmd } },
	{ MODKEY,                       XK_l,      spawn,          {.v = lockcmd } },
	{ MODKEY|ShiftMask,             XK_s,      spawn,          {.v = screenshotcmd } },
	{ 0,                            XK_Print,  spawn,          {.v = gnomeshotcmd } },
	{ MODKEY,                       XK_F8,     spawn,          {.v = greekcmd } },

	{ MODKEY,                       XK_h,      spawn,          SHCMD("xdotool key Left") },
	{ MODKEY,                       XK_j,      spawn,          SHCMD("xdotool key Down") },
	{ MODKEY,                       XK_k,      spawn,          SHCMD("xdotool key Up") },

	{ ControlMask|ALTKEY,           XK_h,      viewrel,        {.i = -1 } },
	{ ControlMask|ALTKEY,           XK_l,      viewrel,        {.i = +1 } },
	{ ControlMask|ALTKEY,           XK_k,      viewrel,        {.i = -1 } },
	{ ControlMask|ALTKEY,           XK_j,      viewrel,        {.i = +1 } },
	{ ShiftMask|ALTKEY,             XK_Left,   tagrel,         {.i = -1 } },
	{ ShiftMask|ALTKEY,             XK_Right,  tagrel,         {.i = +1 } },
	{ ShiftMask|ALTKEY,             XK_Up,     tagrel,         {.i = -1 } },
	{ ShiftMask|ALTKEY,             XK_Down,   tagrel,         {.i = +1 } },

	{ MODKEY,                       XK_F1,     view,           {.ui = 1 << 0 } },
	{ MODKEY,                       XK_F2,     view,           {.ui = 1 << 1 } },
	{ MODKEY,                       XK_F3,     view,           {.ui = 1 << 2 } },
	{ MODKEY,                       XK_F4,     view,           {.ui = 1 << 3 } },
	{ MODKEY,                       XK_F5,     view,           {.ui = 1 << 4 } },
	{ MODKEY,                       XK_F6,     view,           {.ui = 1 << 5 } },

	{ ALTKEY,                       XK_F4,     killclient,     {0} },
	{ ALTKEY,                       XK_Escape, lowerclient,    {0} },
	{ ALTKEY,                       XK_Tab,    focusstack,     {.i = +1 } },
	{ ALTKEY|ShiftMask,             XK_Tab,    focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Right,  focusstack,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Left,   focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Down,   focusstack,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Up,     focusstack,     {.i = -1 } },

	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY|ControlMask,           XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY|ControlMask,           XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
