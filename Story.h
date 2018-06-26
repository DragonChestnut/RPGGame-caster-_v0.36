#ifndef _STORY_H_
#define _STORY_H_

// 初期化
void InitStory(void);

//描画
void DrawStory(void);
//　描画する物語のTexセット
void SetStory();
// 更新 
// 中でEnter押された場合ストーリーモード終了処理してある
void UpdateStory(void);
// ストーリーモードの開始
void StartStory(void);

#endif // _STORY_H_
