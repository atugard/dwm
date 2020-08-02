/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 8;        /* gap pixel between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Iosevka:size=10:antialias=true:hint=true:hintstyle=hintfull; weight=medium: slant=roman: dpi=96", "Font Awesome 5 Free:size=10:antialias=true:hint=true:hintstyle=hintfull; weight=medium: slant=roman: dpi=96" };
static const char dmenufont[]       = "Iosevka:size=10:antialias=true:hint=true:hintstyle=hintfull; weight=medium: slant=roman: dpi=96";
static const char col_black[]       = "#000000";
static const char col_gray1[]       = "#444444";
static const char col_gray2[]       = "#bbbbbb";
static const char col_gray3[]       = "#eeeeee";
static const char col_blue[]        = "#75A4CD";
static const char col_darkblue[]    = "#2a3775";
static const char col_navygreen[]   = "#687c45";
static const char col_red[]         = "#8c3028";
static const char col_purp[]        = "#6c409c";
static const char col_orange[]      = "#f48004";
//static const unsigned int baralpha = 0xd0;
//static const unsigned int borderalpha = 0xd0;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray2, col_black, col_gray1 },
	[SchemeSel]  = { col_gray3, col_darkblue,  col_darkblue  },
};

//static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
//	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
//	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
//};

/* tagging */
static const char *tags[] = { " dev", " dev", " dev", " web ", " web", " misc", " misc", " misc", " read"};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "",      tile },    /* first entry is default */
	{ "",      NULL },    /* no layout function means floating behavior */
	{ "",      monocle },
};

static char browser[]= "firefox";
static char editor[]= "emacs";
static char term[]= "st";
static char reader[]= "zathura";

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", "black", "-nf", col_gray3, "-sb", col_darkblue, "-sf", col_gray3, NULL };
static const char *termcmd[]  = { "tabbed", "-c", "-r", "2", term, "-w", "-e", NULL};
static const char *emacscmd[]  = { editor, NULL};
static const char *browsercmd[]  = { browser, NULL};
static const char *zathuracmd[]  = { "tabbed", "-c", reader, "-e",  NULL};

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,              spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return,         spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_z,              spawn,          {.v = zathuracmd } },
	{ MODKEY,                       XK_backslash,      spawn,          {.v = browsercmd } },
	{ MODKEY,                       XK_apostrophe,     spawn,          {.v = emacscmd } },
	{ MODKEY,                       XK_b,              togglebar,      {0} },
	{ MODKEY,                       XK_j,              focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,              focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,              incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,              incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,              setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,              setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,                                XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,            view,           {0} },
	{ MODKEY,                       XK_w,              killclient,     {0} },
	{ MODKEY,                       XK_t,              setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,              setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,              setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,          setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,          togglefloating, {0} },
	{ MODKEY,                       XK_0,              view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,              tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,          focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,         focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,          tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,         tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,          setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,          setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,          setgaps,        {.i =  0 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,              quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
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

