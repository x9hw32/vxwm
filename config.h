#pragma once

/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* толщина рамки активного окна */
static const unsigned int snap      = 32;       /* расстояние прилипания окон */
static const int showbar            = 1;        /* 1 — показывать панель, 0 — скрыть */
static const int topbar             = 1;        /* 1 — панель вверху, 0 — внизу */
static const char *fonts[]          = { "MesloLGS NF:size=10" };
static const char dmenufont[]       = "MesloLGS NF:size=10";

/* Цветовая палитра под неоново-синюю сакуру */
static MAYBE_CONST char normbgcolor[]           = "#050b14"; /* Фон панели (глубокий иссиня-черный) */
static MAYBE_CONST char normbordercolor[]       = "#11223a"; /* Рамка неактивного окна (темно-синий) */
static MAYBE_CONST char normfgcolor[]           = "#e2f1ff"; /* Текст неактивных элементов */
static MAYBE_CONST char selfgcolor[]            = "#ffffff"; /* Текст активных элементов */
static MAYBE_CONST char selbordercolor[]        = "#0088ff"; /* Рамка активного окна (неоновый синий) */
static MAYBE_CONST char selbgcolor[]            = "#0088ff"; /* Акцент на панели */

static MAYBE_CONST char *colors[][3] = {
       /* fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

#define CENTER_NEW_FLOATING_WINDOWS 1 
#define NEW_FLOATING_WINDOWS_APPEAR_UNDER_CURSOR 0 

/* Зазоры между окнами (gaps) по умолчанию */
#define GAPS 1
#if GAPS
static const unsigned int gappx = 10;
#endif

#if BAR_HEIGHT
static const int user_bh = 0;
#endif

#if BAR_PADDING
static const int vertpad = 5;       
static const int sidepad = 5;       
#endif

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

#if OCCUPIED_TAGS_DECORATION
static const char *occupiedtags[] = { "1+", "2+", "3+", "4+", "5+", "6+", "7+", "8+", "9+" };
#endif

#if INFINITE_TAGS
#define MOVE_CANVAS_STEP 120 
#endif

#if MOVE_RESIZE_WITH_KEYBOARD
#define MOVE_WITH_KEYBOARD_STEP 50 
#define RESIZE_WITH_KEYBOARD_STEP 50 
#endif

/* Правила: все окна по умолчанию открываются в плавающем режиме на текущем воркспейсе (0) */
static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Firefox",  NULL,       NULL,       0,            1,           -1 },
	{ "Telegram", NULL,       NULL,       0,            1,           -1 },
	{ "Alacritty",NULL,       NULL,       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; 
static const int nmaster     = 1;    
static const int resizehints = 1;    
static const int lockfullscreen = 1; 

#define LOCK_MOVE_RESIZE_REFRESH_RATE 1
#if LOCK_MOVE_RESIZE_REFRESH_RATE
static const int refreshrate = 60;  /* Снизил до 60, чтобы Celeron не задыхался при отрисовке */
#endif 

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* F1: Режим тайлинга */
	{ "><>",      NULL },    /* F2: Плавающий режим */
	{ "[M]",      monocle }, /* F3: Моно-режим (стек) */
};

/* Определяем главный модификатор: Super/Win */
#define MODKEY Mod4Mask
#define ALTERNATE_MODKEY Mod1Mask

#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} },

/* хелпер для запуска команд */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* Команды для запуска приложений */
static const char *termcmd[]     = { "alacritty", NULL };
static const char *roficmd[]     = { "rofi", "-show", "drun", NULL };
static const char *browsercmd[]  = { "firefox", NULL };
static const char *rangercmd[]   = { "alacritty", "-e", "ranger", NULL };
static const char *telegramcmd[] = { "telegram-desktop", NULL };
static const char *neovimcmd[]   = { "alacritty", "-e", "nvim", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_space,  spawn,          {.v = roficmd } },    /* Win+Space — Rofi */
	{ MODKEY,                       XK_t,      spawn,          {.v = termcmd } },    /* Win+T — Терминал */
	{ MODKEY,                       XK_b,      spawn,          {.v = browsercmd } }, /* Win+B — Firefox */
	{ MODKEY,                       XK_e,      spawn,          {.v = rangercmd } },  /* Win+E — Ranger */
	{ MODKEY|ShiftMask,             XK_b,      spawn,          {.v = telegramcmd } },/* Win+Shift+B — Telegram */
	{ MODKEY,                       XK_n,      spawn,          {.v = neovimcmd } },  /* Win+N — Neovim */
	{ MODKEY|ShiftMask,             XK_s,      spawn,          SHCMD("maim -s | xclip -selection clipboard -t image/png") }, /* Win+Shift+S — Скриншот */
	
	/* Управление панелью */
	{ MODKEY|ShiftMask,             XK_h,      togglebar,      {0} },                /* Win+Shift+H — Скрыть/показать бар */

	/* Навигация по окнам (Win + Стрелочки) */
	{ MODKEY,                       XK_Left,   focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_Right,  focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_Up,     focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_Down,   focusstack,     {.i = +1 } },

	/* Изменение размеров главного окна клавиатурой (Win + Ctrl + Стрелочки) */
	{ MODKEY|ControlMask,           XK_Left,   setmfact,       {.f = -0.05} },
	{ MODKEY|ControlMask,           XK_Right,  setmfact,       {.f = +0.05} },

	/* Управление воркспейсами и закрытие */
	{ MODKEY,                       XK_Backspace, view,        {0} },                /* Win+Backspace — назад на прошлый ворксейс */
	{ MODKEY,                       XK_q,      killclient,     {0} },                /* Win+Q — закрыть окно */
	
	/* Переключение режимов (Layouts) на F-клавиши */
	{ MODKEY,                       XK_F1,     setlayout,      {.v = &layouts[0]} }, /* Win+F1 — Тайлинг */
	{ MODKEY,                       XK_F2,     setlayout,      {.v = &layouts[1]} }, /* Win+F2 — Плавающий */
	{ MODKEY,                       XK_F3,     setlayout,      {.v = &layouts[2]} }, /* Win+F3 — Моно */
	
	/* Сделать конкретное окно плавающим / полноэкранным */
	{ MODKEY,                       XK_f,      togglefloating, {0} },                /* Win+F — переключить плавание окна */
#define FULLSCREEN 1
#if FULLSCREEN
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },                /* Win+Shift+F — фуллскрин окна */
#endif

	/* Полный выход из vxwm */
	{ MODKEY|ControlMask|Mod1Mask,  XK_q,      quit,           {0} },                /* Win+Ctrl+Alt+Q — выход из WM */

	/* Бинды воркспейсов (Win + 1-9 для перехода, Win + Shift + 1-9 для переноса окна) */
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
#define INFINITE_TAGS 1
#if INFINITE_TAGS
  { ClkRootWin,      MODKEY|ShiftMask,         Button1,        movecanvasmouse,     {.f = 1.5 } }, 
  { ClkClientWin,    MODKEY|ShiftMask,         Button1,        movecanvasmouse,     {.f = 1.5 } }, /* Win+Shift+ЛКМ — тащить окружение */
#endif
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },         /* Win+ЛКМ — тащить окно */
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },         /* Win+СКМ — вернуть в тайлинг */
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },         /* Win+ПКМ — менять размер окна */
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
