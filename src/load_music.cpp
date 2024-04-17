#include <game.h>

// 播放背景音乐
void play_bg_music()
{
    // 第一个参数的格式为 "open 文件路径 alias 别名"
    mciSendString(_T("open static/snake/music.mp3 alias bg_music"), NULL, 0, NULL);
    mciSendString(_T("play bg_music repeat"), NULL, 0, NULL);
}

void play_food_music()
{
    mciSendString(_T("close food_music"), NULL, 0, NULL); // 关闭音乐
    mciSendString(_T("open static/snake/music-food.mp3 alias food_music"), NULL, 0, NULL);
    mciSendString(_T("play food_music"), NULL, 0, NULL);
}