#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <mmsystem.h>
#include <stdbool.h>

#pragma comment(lib, "winmm.lib")

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

// --- MIDI 音高定义 ---
#define NOTE_A5 81
#define NOTE_GS5 80
#define NOTE_FS5 78
#define NOTE_E5 76
#define NOTE_DS5 75
#define NOTE_D5 74
#define NOTE_CS5 73
#define NOTE_C5 72
#define NOTE_B4 71
#define NOTE_AS4 70
#define NOTE_A4 69
#define NOTE_GS4 68
#define NOTE_FS4 66
#define NOTE_E4 64
#define NOTE_D4 62
#define REST 0

// 音符与歌词数据结构
typedef struct
{
    int pitch;          // MIDI 音高
    int duration;       // 持续毫秒 (快速摇滚节奏)
    const char *lyriJp; // 日文 / 罗马音歌词
    const char *lyriCn; // 中文歌词
    int pose;           // 唯阿舞台动作 (0-3)
    int lightColor;     // 舞台灯光主题
} Note;

// 《轻飘飘时间》(Fuwa Fuwa Time) 经典高潮曲谱
Note fuwafuwaScore[] = {
    // --- Intro Riff / 主歌前奏 ---
    {NOTE_A4, 160, "Kimi ", "看 著 ", 0, 1},
    {NOTE_A4, 160, "wo ", "你 ", 1, 1},
    {NOTE_B4, 160, "mi-te-", "的 姿 ", 1, 2},
    {NOTE_CS5, 320, "ru to ", "态，", 2, 2},
    {NOTE_CS5, 160, "i-tsu-", "总 是 ", 0, 3},
    {NOTE_D5, 160, "mo ", "心 跳 ", 1, 3},
    {NOTE_CS5, 160, "do-ki-", "加 ", 2, 1},
    {NOTE_B4, 320, "do-ki! ", "速！", 3, 1},

    {NOTE_A4, 160, "Fu-to ", "不 经 ", 0, 2},
    {NOTE_B4, 160, "me ga ", "意 ", 1, 2},
    {NOTE_CS5, 160, "a-u ", "视 线 ", 2, 3},
    {NOTE_E5, 320, "to, ", "相 遇，", 3, 3},
    {NOTE_D5, 160, "so-ra ", "宛 如 ", 1, 1},
    {NOTE_CS5, 160, "wo ", "飞 上 ", 2, 1},
    {NOTE_B4, 400, "to-bu no! ", "天 空！", 3, 2},

    {REST, 150, "", "", 0, 1},

    // --- 副歌爆发 (Fuwa Fuwa Time!) ---
    {NOTE_CS5, 200, "FU-WA ", "轻 飘 ", 0, 2},
    {NOTE_D5, 200, "FU-WA ", "飘 ", 1, 2},
    {NOTE_E5, 220, "TI-ME! ", "时 间！", 3, 1},
    {REST, 100, "", "", 0, 1},
    {NOTE_A4, 150, "(Fu-wa ", "(轻 飘 ", 0, 3},
    {NOTE_B4, 150, "fu-wa ", "飘 ", 1, 3},
    {NOTE_CS5, 150, "time!) ", "时 间！)", 2, 3},

    {NOTE_CS5, 200, "FU-WA ", "轻 飘 ", 0, 2},
    {NOTE_D5, 200, "FU-WA ", "飘 ", 1, 2},
    {NOTE_E5, 220, "TI-ME! ", "时 间！", 3, 1},
    {REST, 100, "", "", 0, 1},
    {NOTE_A4, 150, "(Fu-wa ", "(轻 飘 ", 0, 3},
    {NOTE_B4, 150, "fu-wa ", "飘 ", 1, 3},
    {NOTE_CS5, 150, "time!) ", "时 间！)", 2, 3},

    // --- 间奏摇滚段落 ---
    {NOTE_E5, 180, "Ka-mi ", "神 啊 ", 0, 1},
    {NOTE_FS5, 180, "sa-ma ", "求 求 ", 1, 1},
    {NOTE_GS5, 180, "o-ne-", "你 ", 2, 2},
    {NOTE_A5, 350, "gai! ", "啦！", 3, 2},

    {NOTE_GS5, 180, "Du-e-", "给 我 ", 1, 3},
    {NOTE_FS5, 180, "tt-o ", "两 人 独 处 的 ", 2, 3},
    {NOTE_E5, 180, "ji-kan ", "时 光 ", 0, 1},
    {NOTE_CS5, 350, "wo! ", "吧！", 3, 1},

    // --- 结尾大合唱高潮 ---
    {NOTE_CS5, 160, "Sui-mi-", "快 睡 著 的 ", 0, 2},
    {NOTE_D5, 160, "n ", "梦 ", 1, 2},
    {NOTE_E5, 160, "bu-so-", "境 ", 2, 3},
    {NOTE_FS5, 320, "ku da ", "里，", 3, 3},
    {NOTE_E5, 160, "yo ", "也 想 ", 1, 1},
    {NOTE_CS5, 160, "wo-sa-", "与 你 ", 2, 1},
    {NOTE_B4, 400, "ku-ni! ", "相 遇！", 3, 2},

    {NOTE_A4, 200, "HTT ", "放 学 后 ", 0, 1},
    {NOTE_B4, 200, "ROCK ", "TEA ", 1, 2},
    {NOTE_CS5, 200, "TIME! ", "TIME!", 2, 3},
    {NOTE_A5, 600, "YEAH!! 🎸", "耶！！🎸", 3, 1}};

// 唯阿 (Yui) & 吉他 (Giita) 姿态动画
const char *yuiPoses[4][7] = {
    {"         ( /  \\ )   🎸Giita!    ",
     "        (  o . o  )             ",
     "         \\   =   /---m           ",
     "       ---/     \\              ",
     "         /  HTT  \\              ",
     "        /_________\\             ",
     "       /___________\\            "},
    {"       \\ ( /  \\ )               ",
     "        \\(  ^ . ^ )  🎸Giita!   ",
     "         \\   v   /--m           ",
     "          /     \\               ",
     "         /  HTT  \\              ",
     "        /_________\\             ",
     "       /___________\\            "},
    {"         ( /  \\ ) /             ",
     "        (  o . o )/  🎸Giita!   ",
     "         \\   O   /---m          ",
     "       ---/     \\               ",
     "         /  HTT  \\              ",
     "        /_________\\             ",
     "       /___________\\            "},
    {"         ✨ 🎸!! ✨              ",
     "       \\ ( /  \\ ) /             ",
     "        \\(  ≧ ∇ ≦ )/              ",
     "         \\   O   /              ",
     "          | HTT  |              ",
     "        /___________\\           ",
     "       /_____________\\          "}};

HMIDIOUT hMidiDevice;

void playMidiNote(int pitch, int velocity)
{
    if (pitch == REST)
        return;
    DWORD msg = 0x00000090 | (pitch << 8) | (velocity << 16);
    midiOutShortMsg(hMidiDevice, msg);
}

void stopMidiNote(int pitch)
{
    if (pitch == REST)
        return;
    DWORD msg = 0x00000080 | (pitch << 8);
    midiOutShortMsg(hMidiDevice, msg);
}

void renderStage(int poseIdx, int colorScheme, const char *lyricsJp, const char *lyricsCn)
{
    const char *lights;
    const char *frame = "\x1b[38;2;255;105;180m"; // HTT 标志性粉色

    switch (colorScheme)
    {
    case 1:
        lights = "\x1b[38;2;255;215;0m";
        break; // 耀金
    case 2:
        lights = "\x1b[38;2;0;225;255m";
        break; // 青蓝
    case 3:
        lights = "\x1b[38;2;255;20;147m";
        break; // 酷粉
    default:
        lights = "\x1b[38;2;255;255;255m";
        break;
    }

    printf("\x1b[H"); // 光标复位无闪烁

    printf("%s/-----------------------------------------------\\\x1b[0m\n", frame);
    printf("%s|\x1b[0m   %s★ HO-KAGO TEA TIME Live! (放学后 Tea Time) ★%s  |\x1b[0m\n", frame, lights, frame);
    printf("%s|-----------------------------------------------|\x1b[0m\n", frame);

    for (int i = 0; i < 7; i++)
    {
        printf("%s|\x1b[0m     %s%s\x1b[0m     %s|\x1b[0m\n",
               frame,
               (i == 0 || i == 1) ? "\x1b[38;2;255;215;0m" : "\x1b[38;2;240;240;240m",
               yuiPoses[poseIdx][i],
               frame);
    }

    printf("%s|===============================================|\x1b[0m\n", frame);
    printf("\x1b[38;2;255;182;193m[=================================================]\x1b[0m\n\n");

    printf(" \x1b[38;2;255;215;0m🎸 ROMAJI  :\x1b[0m \x1b[1m%-32s\x1b[0m\n", lyricsJp);
    printf(" \x1b[38;2;50;205;50m🎤 CHINESE :\x1b[0m \x1b[1m%-32s\x1b[0m\n", lyricsCn);
}

int main()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    SetConsoleOutputCP(65001); // UTF-8

    // 打开 Windows MIDI 设备
    if (midiOutOpen(&hMidiDevice, MIDIMAPPER, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR)
    {
        printf("Error: Cannot open MIDI device!\n");
        return 1;
    }

    // 设置乐器音色为：Overdriven Guitar (过载电吉他 - Program 29)
    midiOutShortMsg(hMidiDevice, 0x00001DC0);

    printf("\x1b[?25l");
    system("cls");

    printf("\n\n");
    printf("   =============================================\n");
    printf("      \x1b[38;2;255;105;180mK-ON! - FUWA FUWA TIME (轻飘飘时间)\x1b[0m\n");
    printf("      \x1b[38;2;255;215;0m演奏者: 放学后 Tea Time (HTT)\x1b[0m\n");
    printf("   =============================================\n\n");
    printf("   唯阿正在调试 Giita，准备开始摇滚演唱会...\n");
    Sleep(2000);
    system("cls");

    int totalNotes = sizeof(fuwafuwaScore) / sizeof(Note);

    for (int i = 0; i < totalNotes; i++)
    {
        Note n = fuwafuwaScore[i];

        renderStage(n.pose, n.lightColor, n.lyriJp, n.lyriCn);

        playMidiNote(n.pitch, 120); // 摇滚高力度发音
        Sleep(n.duration);
        stopMidiNote(n.pitch);
    }

    midiOutClose(hMidiDevice);

    system("cls");
    printf("\n\n   =============================================\n");
    printf("      \x1b[38;2;255;105;180mTHANK YOU!! FUWA FUWA TIME FINISHED! 🎉🎉\x1b[0m\n");
    printf("   =============================================\n\n");

    printf("\x1b[?25h");
    return 0;
}
// operating system 2026 jyy