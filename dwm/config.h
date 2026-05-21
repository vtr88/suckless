/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;
static const unsigned int snap      = 32;
static const int showbar            = 0;
static const int topbar             = 1;
static const char *fonts[]          = { "Roboto:size=9" };
static const char dmenufont[]       = "Roboto:size=9";
static const char col_gray1[]       = "#282828";
static const char col_gray2[]       = "#504945";
static const char col_gray3[]       = "#bdae93";
static const char col_gray4[]       = "#fbf1c7";
static const char col_green[]       = "#b8bb26";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray1, col_green, col_green },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6" };

static const Rule rules[] = {
	/* class          instance       title       tags mask     isfloating   monitor */
	{ "st-256color",  NULL,          NULL,       1 << 0,       1,           -1 },
	{ "St",           NULL,          NULL,       1 << 0,       1,           -1 },
	{ "URxvt",        NULL,          NULL,       1 << 0,       1,           -1 },
	{ "Alacritty",    NULL,          NULL,       1 << 0,       1,           -1 },
	{ "firefox-esr",  NULL,          NULL,       1 << 1,       1,           -1 },
	{ "Spotify",      NULL,          NULL,       1 << 2,       1,           -1 },
	{ "Aseprite",     NULL,          NULL,       1 << 3,       1,           -1 },
	{ "tiled",        NULL,          NULL,       1 << 3,       1,           -1 },
	{ "Renoise",      NULL,          NULL,       1 << 4,       1,           -1 },
	{ "Code",         NULL,          NULL,       1 << 5,       1,           -1 },
	{ "VSCodium",     NULL,          NULL,       1 << 5,       1,           -1 },
	{ "mpv",          NULL,          NULL,       0,            1,           -1 },
	{ "Gimp",         NULL,          NULL,       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55;
static const int nmaster     = 1;
static const int resizehints = 1;
static const int lockfullscreen = 1;
static const int refreshrate = 120;

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "><>",      NULL },
	{ "[]=",      tile },
	{ "[M]",      monocle },
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

/* commands */
static char dmenumon[2] = "0";
static const char *dmenucmd[]     = { "/usr/local/bin/dmenu_run", "-i", "-m", dmenumon, NULL };
static const char *termcmd[]      = { "/usr/local/bin/st", "-e", "tmux", NULL };
static const char *firefoxcmd[]   = { "firefox-esr", NULL };
static const char *spotifycmd[]   = { "/usr/bin/spotify", NULL };
static const char *asepritecmd[]  = { "/usr/bin/aseprite", NULL };
static const char *renoisecmd[]   = { "renoise", NULL };
static const char *lockcmd[]      = { "/usr/local/bin/slock", "/usr/sbin/pm-suspend", NULL };
static const char *screenshotcmd[]= { "flameshot", "gui", NULL };
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
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
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
