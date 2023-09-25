# GUI Application based on Qt with IsLibrary(NdArray base Image Processing Library)

## WARNING
+ タスクブロックベースのGUIアプリケーションは別プログラムに記述しているのでストップ.
+ このプログラムとタスクブロックベースのプログラムを統合すべき.
+ Windows Labtopでの開発をしてたため、そっちを探すこと.

## 背景
+ 自作ライブラリIsLibraryの実行環境が必要.
+ コンベンショナルな画像処理/3D処理技術をGUIで使用できる環境が必要
+ Congex DesignerやUnityのようなC#ベースのアプリケーションは存在するが, C/C++オンリーなアプリケーション環境が見当たらない.

## 目的
+ 自作ライブラリIsLibraryの有効性実証基盤の構築.
+ CMake環境での別リポジトリとの自動統合によるアプリケーションビルドの自動化.
+ OpenCV/Direct3D/MetalのようなCG技術基盤の構築.

## 終了条件
+ 自分が納得するまで

## ロードマップ



## 機能要件
+ CognexDesignerのようなブロックグラフによる画像処理チェイン
+ Unityのようなスクリプト機能(dllモジュール+実行時ロード)
+ 各ブロック(タスクブロック)でのタスク(画像処理結果)比較機能
+ 画像/データのIO機能(USB, IP, TCP/UDP, etc..)
+ スルー画像の表示機能
+ タスクブロック間のデータ受け渡し機能
+ スクリプトビルド機能
+ タスクチェインのループ機能(イベントループ的なやつ)
+ 非同期処理機能

## 非機能要件
+ CMake
+ Qt
+ IsLibrary
+ OpenCV
+ Direct3D
+ OpenCV
+ Metal
+ Tensorflow
+ Tensorflow Lite
+ Pytorch
+ 
