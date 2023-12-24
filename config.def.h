/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 4;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappx     = 0;
static const unsigned int gappih    = 8;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 8;       /* vert inner gap between windows */
static const unsigned int gappoh    = 8;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 8;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
// static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static int floatposgrid_x           = 5;        /* float grid columns */
static int floatposgrid_y           = 5;        /* float grid rows */
static const char *fonts[]          = { "monospace:size=12" };
static const char dmenufont[]       = "monospace:size=12";
static const char col1[]            = "#ffffff";
static const char col2[]            = "#ffffff";
static const char col3[]            = "#ffffff";
static const char col4[]            = "#ffffff";
static const char col5[]            = "#ffffff";
static const char col6[]            = "#ffffff";
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";

enum { SchemeNorm, SchemeCol1, SchemeCol2, SchemeCol3, SchemeCol4,
       SchemeCol5, SchemeCol6, SchemeSel }; /* color schemes */

static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
	     [SchemeCol1]  = { normfgcolor, normbgcolor, normbordercolor },
	     [SchemeCol2]  = { normfgcolor, normbgcolor, normbordercolor },
	     [SchemeCol3]  = { normfgcolor, normbgcolor, normbordercolor },
	     [SchemeCol4]  = { normfgcolor, normbgcolor, normbordercolor },
	     [SchemeCol5]  = { normfgcolor, normbgcolor, normbordercolor },
	     [SchemeCol6]  = { normfgcolor, normbgcolor, normbordercolor },
};

/* tagging */
#define TAGLENGTH 9
static const char *tags[][TAGLENGTH] = {
	{ "", "󰙯", "", "󰓓", "", "", "", "", "󰢹" },
  { "1", "2", "3", "4", "5", "6", "7", "8", "9" },
//	{ "", "", "", "󰢹", "" },
};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   floatpos   monitor */
	{ "Gimp",     	NULL,       NULL,       0,            1,         NULL,      -1 },
	{ "Firefox",  	NULL,       NULL,       1,       0,         NULL,       0 },
 	{ "quake.bin", 	NULL,       NULL,       1 << 2,       0,         NULL,       0 },
 	{ "discord",  	NULL,       NULL,       1 << 1,       0,         NULL,       0 },
 	{ "obs",      	NULL,       NULL,       1 << 6,       0,         NULL,       0 },
 	{ "Steam",    	NULL,       NULL,       1 << 3,       0,         NULL,       0 },
 	{ "steam",    	NULL,       NULL,       1 << 3,       0,         NULL,       0 },
  { "blocks",     NULL,       NULL,       0,            1,         "100% 20% 800W 400H",     -1 },
  { "bigblock", NULL,       NULL,       0,            1,           "100% 20% 1500W 900H",    -1 },
  { "e1",       NULL,       NULL,       0,            1,           "0x 0y 800W 800H",       -1 },
  { "e2",       NULL,       NULL,       0,            1,           "9999X 0y 800W 800H",    -1 },
  { "e3",       NULL,       NULL,       0,            1,           "0x 9999y 800W 800H",    -1 },
  { "e4",       NULL,       NULL,       0,            1,           "9999x 9999y 800W 800H", -1 },
  { "e5",       NULL,       NULL,       0,            1,           "-1x -1y 9999W 800H",    -1 },
  { "e6",       NULL,       NULL,       0,            1,           "-1x 9999y 9999W 800H",  -1 },
  { "e7",       NULL,       NULL,       0,            1,           "-1x -1y 800W 9999H",    -1 },
  { "e8",       NULL,       NULL,       0,            1,           "9999x -1y 800W 9999H",  -1 },
  { "e9",       NULL,       NULL,       0,            1,           "50% 50% 800W 800H",     -1 },
  { "e10",      NULL,       NULL,       0,            1,           "-1x -1y 50% 50%",       -1 },
  { "e11",      NULL,       NULL,       0,            1,           "0% 0% 800W 800H",       -1 },
  { "e12",      NULL,       NULL,       0,            1,           "100% 0% 800W 800H",     -1 },
  { "e13",      NULL,       NULL,       0,            1,           "0% 100% 800W 800H",     -1 },
  { "e14",      NULL,       NULL,       0,            1,           "100% 100% 800W 800H",   -1 },
  { "e15",      NULL,       NULL,       0,            1,           "-1x -1y 100% 800H",     -1 },
  { "e16",      NULL,       NULL,       0,            1,           "-1x 100% 100% 800H",    -1 },
  { "e17",      NULL,       NULL,       0,            1,           "-1x -1y 800W 100%",     -1 },
  { "e18",      NULL,       NULL,       0,            1,           "100% -1y 800W 100%",    -1 },
  { "e19",      NULL,       NULL,       0,            1,           "50% 50% 50% 50%",       -1 },
  { "e20",      NULL,       NULL,       0,            1,           "0m 0m 800W 600H",       -1 },
  { "e21",      NULL,       NULL,       0,            1,           NULL,                    -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
};

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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *dmenudesktopcmd[] = { "j4-dmenu-desktop", "--term=alacritty", NULL }; // first trying just to get it to work
static const char *termcmd[]  = { "alacritty", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
  { MODKEY|ShiftMask,             XK_p,      spawn,          {.v = dmenudesktopcmd } },                 
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|Mod4Mask,              XK_h,      incrgaps,       {.i = +1 } },
	{ MODKEY|Mod4Mask,              XK_l,      incrgaps,       {.i = -1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_h,      incrogaps,      {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_l,      incrogaps,      {.i = -1 } },
	{ MODKEY|Mod4Mask|ControlMask,  XK_h,      incrigaps,      {.i = +1 } },
	{ MODKEY|Mod4Mask|ControlMask,  XK_l,      incrigaps,      {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_0,      togglegaps,     {0} },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
	{ MODKEY,                       XK_y,      incrihgaps,     {.i = +1 } },
	{ MODKEY,                       XK_o,      incrihgaps,     {.i = -1 } },
	{ MODKEY|ControlMask,           XK_y,      incrivgaps,     {.i = +1 } },
	{ MODKEY|ControlMask,           XK_o,      incrivgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_y,      incrohgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask,              XK_o,      incrohgaps,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_y,      incrovgaps,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_o,      incrovgaps,     {.i = -1 } },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_o,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
  { MODKEY,			                  XK_minus,	 spawn,		       SHCMD("pamixer --allow-boost -d 5; kill -36 $(pidof dwmblocks)") },
  { MODKEY|ShiftMask,	  	        XK_minus,	 spawn,		       SHCMD("pamixer --allow-boost -d 15; kill -36 $(pidof dwmblocks)") },
	{ MODKEY,			                  XK_equal,	 spawn,		       SHCMD("pamixer --allow-boost -i 5; kill -36 $(pidof dwmblocks)") },
	{ MODKEY|ShiftMask,		          XK_equal,	 spawn,		       SHCMD("pamixer --allow-boost -i 15; kill -36 $(pidof dwmblocks)") },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_F5,     xrdb,           {.v = NULL } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
  { 0,                            XF86XK_AudioMute,		      spawn,		SHCMD("pamixer -t; kill -36 $(pidof dwmblocks)") },
	{ 0,                            XF86XK_AudioRaiseVolume,	spawn,		SHCMD("pamixer --allow-boost -i 3; kill -36 $(pidof dwmblocks)") },
	{ 0,                            XF86XK_AudioLowerVolume,	spawn,		SHCMD("pamixer --allow-boost -d 3; kill -36 $(pidof dwmblocks)") },
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigdwmblocks,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigdwmblocks,   {.i = 5} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

