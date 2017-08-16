# Orphe-Music-Controller-Sample
Orphe Hub &lt;-> OSC &lt;-> openFrameworks

You can controll music by using Orphe and HUB App.  
Please put the sound file in bin/data/music.

sample sound file by Open JTalk  
http://open-jtalk.sp.nitech.ac.jp/index.php

<img width="1025" alt="omc_ui" src="https://user-images.githubusercontent.com/9309605/29307516-30599570-81dd-11e7-9584-f276efd9b4dc.png">

## Requirements
- Orphe  
http://orphe.shoes
- HUB App  
https://sites.google.com/view/orphe-developers/hub-app
- openFrameworks 0.9.8  
http://openframeworks.cc
### addons
- ofxOsc
- ofxGui

## Demo
The application used in demos is different from Orphe-Music-Controller-Sample.  

[![IMAGE ALT TEXT HERE](http://img.youtube.com/vi/mOG9A0VkJno/0.jpg)](http://www.youtube.com/watch?v=YOUTUBE_VIDEO_ID_HERE)  
https://youtu.be/mOG9A0VkJno  
[![IMAGE ALT TEXT HERE](http://img.youtube.com/vi/UZJJ25Yc6ls/0.jpg)](http://www.youtube.com/watch?v=YOUTUBE_VIDEO_ID_HERE)  
https://youtu.be/UZJJ25Yc6ls

## How to use
開発環境のない方でも以下URLよりお試しいただけます。  
その場合、サウンドファイルを入れる場所が異なりますのでご注意ください。  
1.appファイルを右クリックして「パッケージの内容を表示」を選択  
2.Contents/Resources/data/music内にサウンドファイルを入れる  
https://drive.google.com/file/d/0B00sNUjrVFMIUkhCdFJ4WmZXb0U/view?usp=sharing
### アプリ起動前にすること
- OrpheとHUB Appを接続しておく
- bin/data/music以下にサウンドファイル（wav、mp3）を入れておく
### 画面の説明
#### INFO
- heel count：かかと踏み込み回数（3回まで）
- volume：音量
- speed：再生速度
- position：再生位置
- loaded sound num：ロードした楽曲の数（10曲まで）
#### PLAYLIST
ロードしたサウンドファイル名の一覧が表示される（英語表記のみ、ABC順）
#### OMC GUI
- soundCircle：レコードプレイヤー的なビジュアル
- cone：Orpheの姿勢を表示
- heelElapsedTime：かかと踏み込み回数の認識間隔（低いとすぐ回数が0にリセットされる）
- heelLock：かかと踏み込みを認識したくないときにチェック
- toeMode：再生速度の加算パラメーターにつま先踏み込みジェスチャーを使用
- gyroMode：再生速度の加算パラメーターにOrpheの角速度の値を使用
- gyroDirectMode：再生速度にOrpheの角速度が直接反映される
- toeUpParam：高いほど再生速度が上がりやすくなる（toeMode設定時）
- gyroUpParam：高いほど再生速度が上がりやすくなる（gyroMode設定時）
- gyroDirectParam：高いほど再生速度が上がりやすくなる（gyroDirectMode設定時）
- downParam：高いほど再生速度が下がりやすくなる（toeMode、gyroMode設定時）
### 操作方法
#### Orphe
- 左かかと3回踏み込み：再生・停止
- 右かかと3回踏み込み：曲の変更
#### キーボード
- f：フルスクリーン表示
- l：サウンドファイルのロード&アンロード
- s：再生・停止
- p：一時停止
- n：曲の変更
- i：INFO&PLAYLIST&OMC GUIの表示
- escキー：アプリの終了
