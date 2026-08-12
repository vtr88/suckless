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
	/* Tema inspirado em gruvbox, com destaque verde em vez do azul padrao. */
	[SchemeNorm] = { "#bdae93", "#282828" },
	[SchemeSel] = { "#282828", "#b8bb26" },
	[SchemeOut] = { "#282828", "#83a598" },
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
