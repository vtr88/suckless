/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[]        = "Noto Sans:style=Bold:size=10";
static const char* normbgcolor  = "#2e2821";
static const char* normfgcolor  = "#bdca58";
static const char* selbgcolor   = "#241f1a";
static const char* selfgcolor   = "#ff9f3f";
static const char* urgbgcolor   = "#ff9f3f";
static const char* urgfgcolor   = "#241f1a";
static const char before[]      = "<";
static const char after[]       = ">";
static const char titletrim[]   = "...";
static const int  tabwidth      = 200;
static const Bool foreground    = True;
static       Bool urgentswitch  = False;

/*
 * Where to place a new tab when it is opened. When npisrelative is True,
 * then the current position is changed + newposition. If npisrelative
 * is False, then newposition is an absolute position.
 */
static int  newposition   = 1;
static Bool npisrelative  = True;

#define SETPROP(p) { \
        .v = (char *[]){ "/bin/sh", "-c", \
                "prop=\"`xwininfo -children -id $1 | grep '^     0x' |" \
                "sed -e's@^ *\\(0x[0-9a-f]*\\) \"\\([^\"]*\\)\".*@\\1 \\2@' |" \
                "xargs -0 printf %b | dmenu -l 10 -w $1`\" &&" \
                "xprop -id $1 -f $0 8s -set $0 \"$prop\"", \
                p, winid, NULL \
        } \
}

#define BOOKMARK(n) { \
	.v = (char *[]){ "surf-bookmark", winid, n, NULL } \
}

#define MODKEY ControlMask
static const Key keys[] = {
	/* modifier             key        function     argument */
	{ MODKEY,               XK_t,      focusonce,   { 0 } },
	{ MODKEY,               XK_t,      spawn,       { 0 } },

	{ MODKEY|ShiftMask,     XK_l,      rotate,      { .i = +1 } },
	{ MODKEY|ShiftMask,     XK_h,      rotate,      { .i = -1 } },
	{ MODKEY|ShiftMask,     XK_j,      movetab,     { .i = -1 } },
	{ MODKEY|ShiftMask,     XK_k,      movetab,     { .i = +1 } },
	{ MODKEY,               XK_Tab,    rotate,      { .i = 0 } },

	{ MODKEY,               XK_grave,  spawn,       SETPROP("_TABBED_SELECT_TAB") },
	{ MODKEY,               XK_1,      move,        { .i = 0 } },
	{ MODKEY,               XK_2,      move,        { .i = 1 } },
	{ MODKEY,               XK_3,      move,        { .i = 2 } },
	{ MODKEY,               XK_4,      move,        { .i = 3 } },
	{ MODKEY,               XK_5,      move,        { .i = 4 } },
	{ MODKEY,               XK_6,      move,        { .i = 5 } },
	{ MODKEY,               XK_7,      move,        { .i = 6 } },
	{ MODKEY,               XK_8,      move,        { .i = 7 } },
	{ MODKEY,               XK_9,      move,        { .i = 8 } },
	{ MODKEY,               XK_0,      move,        { .i = 9 } },
	{ MODKEY|ShiftMask,     XK_1,      spawn,       BOOKMARK("1") },
	{ MODKEY|ShiftMask,     XK_2,      spawn,       BOOKMARK("2") },
	{ MODKEY|ShiftMask,     XK_3,      spawn,       BOOKMARK("3") },
	{ MODKEY|ShiftMask,     XK_4,      spawn,       BOOKMARK("4") },
	{ MODKEY|ShiftMask,     XK_5,      spawn,       BOOKMARK("5") },
	{ MODKEY|ShiftMask,     XK_6,      spawn,       BOOKMARK("6") },
	{ MODKEY|ShiftMask,     XK_7,      spawn,       BOOKMARK("7") },
	{ MODKEY|ShiftMask,     XK_8,      spawn,       BOOKMARK("8") },
	{ MODKEY|ShiftMask,     XK_9,      spawn,       BOOKMARK("9") },
	{ MODKEY|ShiftMask,     XK_0,      spawn,       BOOKMARK("10") },

	{ MODKEY,               XK_q,      killclient,  { 0 } },

	{ MODKEY,               XK_u,      focusurgent, { 0 } },
	{ MODKEY|ShiftMask,     XK_u,      toggle,      { .v = (void*) &urgentswitch } },

	{ 0,                    XK_F11,    fullscreen,  { 0 } },
};
