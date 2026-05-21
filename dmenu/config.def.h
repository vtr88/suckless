/* See LICENSE file for copyright and license details. */
/* Default settings; can be overriden by command line. */

static int topbar = 1;                      /* -b  option; if 0, dmenu appears at bottom     */
/* Fonte igual ao resto do meu desktop atual. */
static const char *fonts[] = {
	"Roboto:size=9"
};
static const char *prompt      = NULL;      /* -p  option; prompt to the left of input field */
static const char *colors[SchemeLast][2] = {
	/*     fg         bg       */
	/* Tema inspirado em gruvbox, com destaque verde em vez do azul padrao. */
	[SchemeNorm] = { "#bdae93", "#282828" },
	[SchemeSel] = { "#282828", "#b8bb26" },
	[SchemeOut] = { "#282828", "#83a598" },
};
/* Menu vertical para ficar mais perto do fluxo que eu tinha no rofi. */
static unsigned int lines      = 3;
/* Ajustes visuais locais: menu centralizado, mais alto, com largura fixa e borda. */
static unsigned int lineheight = 28;
static unsigned int centered   = 1;
static unsigned int menuwidth  = 720;
static unsigned int borderpx   = 2;

/*
 * Characters not considered part of a word while deleting words
 * for example: " /?\"&[]"
 */
static const char worddelimiters[] = " ";
