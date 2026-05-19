/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* толщина рамки активного окна в пикселях */
static const unsigned int gappx     = 10;       /* зазоры (gaps) между окнами в пикселях */
static const unsigned int snap      = 32;       /* расстояние прилипания окон */
static const int showbar            = 1;        /* 1 — показывать панель по умолчанию, 0 — скрыть */
static const int topbar             = 1;        /* 1 — панель вверху, 0 — панель внизу */
static const char *fonts[]          = { "MesloLGS NF:size=10" };
static const char dmenufont[]       = "MesloLGS NF:size=10";

/* Цветовая палитра под неоново-синюю сакуру */
static const char col_gray1[]       = "#050b14"; /* Фон панели (глубокий иссиня-черный) */
static const char col_gray2[]       = "#11223a"; /* Рамка неактивного окна (темно-синий) */
static const char col_gray3[]       = "#e2f1ff"; /* Цвет текста неактивных элементов (светло-голубой) */
static const char col_gray4[]       = "#ffffff"; /* Цвет текста активных элементов (белый) */
static const char col_cyan[]        = "#0088ff"; /* Рамка активного окна и акцент (неоновый синий) */
static const char *colors[][3]      = {
	/* fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* Названия воркспейсов (используем цифры, как ты просил) */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

/* Правила для окон: все открываются в плавающем режиме на текущем воркспейсе (0) */
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Firefox",  NULL,       NULL,       0,            1,           -1 },
	{ "Telegram", NULL,       NULL,       0,            1,           -1 },
	{ "Alacritty",NULL,       NULL,       0,            1,           -1 },
};

/* Свойства макетов (layouts) */
static const float mfact     = 0.55; /* пропорция главного окна (55% экрана) */
static const int nmaster     = 1;    /* количество окон в мастер-зоне */
static const int resizehints = 1;    /* 1 — уважать подсказки размера окон, 0 — форсировать тайлинг */

static const Layout layouts[] = {
	/* Символ отображения макета в баре и функция */
	{ "[]=",      tile },    /* F1: Режим тайлинга */
	{ "><>",      NULL },    /* F2: Плавающий режим (без макета) */
	{ "[M]",      monocle }, /* F3: Моно-режим (стек) */
};

/* Определяем главный модификатор: Super/Win */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} },

/* Хелпер для запуска программ */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* Команды для запуска софта */
static const char *termcmd[]  = { "alacritty", NULL };
static const char *roficmd[]  = { "rofi", "-show", "drun", NULL };
static const char *browsercmd[] = { "firefox", NULL };
static const char *rangercmd[]  = { "alacritty", "-e", "ranger", NULL };
static const char *telegramcmd[] = { "telegram-desktop", NULL };
static const char *neovimcmd[]  = { "alacritty", "-e", "nvim", NULL };
static const char *screenshotcmd[] = { "maim", "-s", "|", "xclip", "-selection", "clipboard", "-t", "image/png", NULL };

static const Key keys[] = {
	/* Модификатор          Клавиша    Функция         Аргумент */
	{ MODKEY,               XK_space,  spawn,          {.v = roficmd } },    /* Win+Space — Rofi */
	{ MODKEY,               XK_t,      spawn,          {.v = termcmd } },    /* Win+T — Терминал */
	{ MODKEY,               XK_b,      spawn,          {.v = browsercmd } }, /* Win+B — Firefox */
	{ MODKEY,               XK_e,      spawn,          {.v = rangercmd } },  /* Win+E — Ranger */
	{ MODKEY|ShiftMask,     XK_b,      spawn,          {.v = telegramcmd } },/* Win+Shift+B — Telegram */
	{ MODKEY,               XK_n,      spawn,          {.v = neovimcmd } },  /* Win+N — Neovim */
	{ MODKEY|ShiftMask,     XK_s,      spawn,          SHCMD("maim -s | xclip -selection clipboard -t image/png") }, /* Win+Shift+S — Скриншот */
	
	/* Управление панелью */
	{ MODKEY|ShiftMask,     XK_h,      togglebar,      {0} },                /* Win+Shift+H — Скрыть/показать бар */

	/* Навигация по окнам (Win + Стрелочки) */
	{ MODKEY,               XK_Left,   focusstack,     {.i = -1 } },
	{ MODKEY,               XK_Right,  focusstack,     {.i = +1 } },
	{ MODKEY,               XK_Up,     focusstack,     {.i = -1 } },
	{ MODKEY,               XK_Down,   focusstack,     {.i = +1 } },

	/* Изменение размеров (Win + Ctrl + Стрелочки) */
	{ MODKEY|ControlMask,   XK_Left,   setmfact,       {.f = -0.05} },
	{ MODKEY|ControlMask,   XK_Right,  setmfact,       {.f = +0.05} },

	/* Управление воркспейсами и закрытие */
	{ MODKEY,               XK_Backspace, view,        {0} },                /* Win+Backspace — назад на прошлый тег */
	{ MODKEY,               XK_q,      killclient,     {0} },                /* Win+Q — закрыть окно */
	
	/* Переключение режимов (Layouts) на F-клавиши */
	{ MODKEY,               XK_F1,     setlayout,      {.v = &layouts[0]} }, /* Win+F1 — Тайлинг */
	{ MODKEY,               XK_F2,     setlayout,      {.v = &layouts[1]} }, /* Win+F2 — Плавающий */
	{ MODKEY,               XK_F3,     setlayout,      {.v = &layouts[2]} }, /* Win+F3 — Моно */
	
	/* Сделать конкретное окно плавающим / полноэкранным */
	{ MODKEY,               XK_f,      togglefloating, {0} },                /* Win+F — переключить плавание окна */
	{ MODKEY|ShiftMask,     XK_f,      togglefullscreen, {0} },              /* Win+Shift+F — фуллскрин окна */

	/* Выход из vxwm */
	{ MODKEY|ControlMask|Mod1Mask, XK_q, quit,         {0} },                /* Win+Ctrl+Alt+Q — выход из WM */

	/* Бинды для воркспейсов (Win + 1-9 и Win + Shift + 1-9) */
	TAGKEYS(                XK_1,                      0)
	TAGKEYS(                XK_2,                      1)
	TAGKEYS(                XK_3,                      2)
	TAGKEYS(                XK_4,                      3)
	TAGKEYS(                XK_5,                      4)
	TAGKEYS(                XK_6,                      5)
	TAGKEYS(                XK_7,                      6)
	TAGKEYS(                XK_8,                      7)
	TAGKEYS(                XK_9,                      8)
};

/* Бинды мыши */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinMethod,         0,              Button1,        setlayout,      {0} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} }, /* Win+ЛКМ — тащить окно */
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} }, /* Win+СКМ — вернуть в тайлинг */
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} }, /* Win+ПКМ — менять размер */
	{ ClkClientWin,         MODKEY|ShiftMask, Button1,      movemouse,      {0} }, /* Win+Shift+ЛКМ — тащить окружение/окно */
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
