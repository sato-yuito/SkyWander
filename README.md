ゲーム会社様に提出するためのゲーム制作
天空都市(空中庭園)をイメージしたアスレチックゲーム

敵も今は仮モデルだが二種類、三種類に増やしていく予定。ただ追跡したさいプレイヤーと重なってしまうためそこも直す予定です。あと攻撃もこだわりを持ちたいと思っています。

プレイヤーは操作だけがほぼできておりまだ敵を倒す方法やプレイヤーのHpをまだきめていないのでそこもおいおい決める予定です。(モデルは仮モデルなのでモデルを追加したりアニメーションを適用させていきたいと思っています)

アスレチックゲームのマップのデザイン、スタート、ゴールは未実装(ゴールはお宝をとったらゴールっていうのにしていきたいです）

-----基本操作-----
WASD 前後左右移動
SPACE ジャンプ
左SHIFT+移動キー　ダッシュ

-----アピールポイント-----
プレイヤーと敵のアニメーションにこだわりたいと思っております（未実装)
プレイヤーが敵に対してカウンター攻撃を行う際のカメラワークも実装したいです。
今は敵の移動を頑張ったので見てほしいです。(追跡アルゴリズムを使って実装しました)




----フォルダ構成-----

│  .gitattributes
│  .gitignore
│  Enemy.cpp
│  Enemy.h
│  Floor.cpp
│  Floor.h
│  GameBaseDx11.vcxproj
│  GameBaseDx11.vcxproj.filters
│  GameBaseDx11.vcxproj.user
│  GameOverScene.cpp
│  GameOverScene.h
│  Map.cpp
│  Map.h
│  Player.cpp
│  Player.h
│  PlayScene.cpp
│  PlayScene.h
│  README.md
│  skyWander.sln
│  TestScene.cpp
│  TestScene.h
│  TittleScene.cpp
│  TittleScene.h
│
├─Assets
│  │  char.png
│  │  defaultParticle.png
│  │  Enemy.fbx
│  │  imgui.ini
│  │  Map.csv
│  │  Map.fbx
│  │  PavingStones131_2K-PNG_Color.png
│  │  PavingStones131_2K-PNG_NormalDX.png
│  │  Player.fbx
│  │  setup.ini
│  │  StartScreen.png
│  │  TestairMap.fbx
│  │  TestEnemBallet.fbx
│  │
│  ├─DebugCollision
│  │      BoxCollider.fbx
│  │      SphereCollider.fbx
│  │
│  └─Shader
│          BillBoard.hlsl
│          Debug3D.hlsl
│          Simple2D.hlsl
│          Simple3D.hlsl
│
├─Engine
│  │  Audio.cpp
│  │  Audio.h
│  │  BillBoard.cpp
│  │  BillBoard.h
│  │  BoxCollider.cpp
│  │  BoxCollider.h
│  │  Camera.cpp
│  │  Camera.h
│  │  Collider.cpp
│  │  Collider.h
│  │  CsvReader.cpp
│  │  CsvReader.h
│  │  Debug.cpp
│  │  Debug.h
│  │  Direct3D.cpp
│  │  Direct3D.h
│  │  Fbx.cpp
│  │  Fbx.h
│  │  FbxParts.cpp
│  │  FbxParts.h
│  │  GameObject.cpp
│  │  GameObject.h
│  │  Global.h
│  │  Image.cpp
│  │  Image.h
│  │  Input.cpp
│  │  Input.h
│  │  Main.cpp
│  │  Model.cpp
│  │  Model.h
│  │  RootObject.cpp
│  │  RootObject.h
│  │  SceneManager.cpp
│  │  SceneManager.h
│  │  SphereCollider.cpp
│  │  SphereCollider.h
│  │  Sprite.cpp
│  │  Sprite.h
│  │  Text.cpp
│  │  Text.h
│  │  Texture.cpp
│  │  Texture.h
│  │  Transform.cpp
│  │  Transform.h
│  │  VFX.cpp
│  │  VFX.h
│  │
│  └─ImGui
│          imconfig.h
│          imgui.cpp
│          imgui.h
│          imgui_draw.cpp
│          imgui_impl_dx11.cpp
│          imgui_impl_dx11.h
│          imgui_impl_win32.cpp
│          imgui_impl_win32.h
│          imgui_internal.h
│          imgui_tables.cpp
│          imgui_widgets.cpp
│          imstb_rectpack.h
│          imstb_textedit.h
│          imstb_truetype.h
│
├─x64
│  └─Debug
│      │  Audio.obj
│      │  BillBoard.cso
│      │  BillBoard.obj
│      │  BoxCollider.obj
│      │  Camera.obj
│      │  Collider.obj
│      │  CsvReader.obj
│      │  Debug.obj
│      │  Debug3D.cso
│      │  Direct3D.obj
│      │  Enemy.obj
│      │  Fbx.obj
│      │  FbxParts.obj
│      │  Floor.obj
│      │  GameBaseDx11.exe
│      │  GameBaseDx11.exe.recipe
│      │  GameBaseDx11.ilk
│      │  GameBaseDx11.log
│      │  GameBaseDx11.pdb
│      │  GameBaseDx11.vcxproj.FileListAbsolute.txt
│      │  GameObject.obj
│      │  GameOverScene.obj
│      │  Image.obj
│      │  imgui.obj
│      │  imgui_draw.obj
│      │  imgui_impl_dx11.obj
│      │  imgui_impl_win32.obj
│      │  imgui_tables.obj
│      │  imgui_widgets.obj
│      │  Input.obj
│      │  Main.obj
│      │  Map.obj
│      │  Model.obj
│      │  Player.obj
│      │  RootObject.obj
│      │  SceneManager.obj
│      │  Simple2D.cso
│      │  Simple3D.cso
│      │  SphereCollider.obj
│      │  Sprite.obj
│      │  TestScene.obj
│      │  Text.obj
│      │  Texture.obj
│      │  TittleScene.obj
│      │  Transform.obj
│      │  vc143.idb
│      │  vc143.pdb
│      │  VFX.obj
│      │
│      └─GameBaseDx11.tlog
│              CL.command.1.tlog
│              CL.read.1.tlog
│              CL.write.1.tlog
│              fxc.command.1.tlog
│              fxc.read.1.tlog
│              fxc.write.1.tlog
│              GameBaseDx11.lastbuildstate
│              link.command.1.tlog
│              link.read.1.tlog
│              link.write.1.tlog
│
└─実行動画


