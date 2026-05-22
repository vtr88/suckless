/* Usuario/grupo sem privilegios para o processo depois de travar a tela. */
static const char *user  = "nobody";
static const char *group = "nogroup";

static const char *colorname[NUMCOLS] = {
	[INIT] =   "black",     /* tela bloqueada sem input */
	[INPUT] =  "#b8bb26",   /* verde gruvbox enquanto a senha esta correta/ativa */
	[FAILED] = "#af3a03",   /* marrom escuro para erro, menos agressivo que vermelho */
};

/* Limpar o input conta como falha visual, evitando ficar sem feedback. */
static const int failonclear = 1;
