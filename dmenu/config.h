/* See LICENSE file for copyright and license details. */
/* Default settings; can be overriden by command line. */

static int topbar = 1;                      /* -b  option; if 0, dmenu appears at bottom     */
/*
 * Fonte pequena e discreta para o menu ficar com cara de ferramenta,
 * nao de launcher grande. Mantem coerencia com o restante do X.
 */
static const char *fonts[] = {
	"Roboto:size=9"
};
static const char *prompt      = NULL;      /* -p  option; prompt to the left of input field */
static const char *colors[SchemeLast][2] = {
	/*     fg         bg       */
	/* Mesma paleta quente usada pelo dwm e pelo tabbed. */
	[SchemeNorm] = { "#bdca58", "#2e2821" },
	[SchemeSel] = { "#ff9f3f", "#241f1a" },
	[SchemeOut] = { "#241f1a", "#ff9f3f" },
};
/*
 * Menu vertical curto: tres linhas foram suficientes para uso diario e
 * evitam aquele painel grande demais no meio da tela.
 */
static unsigned int lines      = 3;
/*
 * Ajustes visuais locais:
 * - centralizado para lembrar o rofi antigo;
 * - largura fixa para nao variar conforme o texto;
 * - borda pequena para destacar em cima do compositor/picom.
 */
static unsigned int lineheight = 28;
static unsigned int centered   = 1;
static unsigned int menuwidth  = 720;
static unsigned int borderpx   = 2;
static unsigned int backdrop   = 1;
static float backdropopacity   = 0.25;

/*
 * Characters not considered part of a word while deleting words
 * for example: " /?\"&[]"
 */
static const char worddelimiters[] = " ";
