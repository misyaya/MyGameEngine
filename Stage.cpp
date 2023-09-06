#include "Stage.h"
#include "Engine/Model.h"
#include "resource.h"
#include "Engine/Direct3D.cpp"


void Stage::SetBlockType(int _x, int _z, BLOCKTYPE _type)
{ 
    //エラーチェック　範囲内の値かどうかしたほうがいい
    table_[_x][_z].type = _type;
}

void Stage::SetBlockHeight(int _x, int _z, int _height)
{
    //エラーチェック　範囲内の値かどうかしたほうがいい
    table_[_x][_z].height = _height;
}

//コンストラクタ
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"), hModel_{-1,-1,-1,-1,-1}
{
    for (int i = 0; i < MODEL_NUM; i++)
    {
        hModel_[i] = -1;
    }

    for (int x = 0; x < XSIZE; x++)
    {
        for (int z = 0; z < ZSIZE; z++)
        {
            SetBlockType(x, z, DEFAULT);
        }
    }
}

//デストラクタ
Stage::~Stage()
{
}

//初期化
void Stage::Initialize()
{
    string modelname[] = {
        "BoxDefault.fbx",
        "BoxBrick.fbx",
        "BoxGrass.fbx",
        "BoxSand.fbx",
        "BoxWater.fbx",
    };
    string fname_base = "Assets/";

    for (int i = 0; i < MODEL_NUM; i++)
    {
        //モデルデータのロード
        hModel_[i] = Model::Load(fname_base + modelname[i]);
       assert(hModel_[i] >= 0);
    }
  
    //tableにブロックのタイプをセットしてやろう！
    for (int x = 0; x < ZSIZE; x++)
    {
        for (int z = 0; z < XSIZE; z++)
        {
            SetBlockType(x, z,( BLOCKTYPE)(z%5));
            SetBlockHeight(x, z, x % 5);
        }
    }
}

//更新
void Stage::Update()
{
    float w = (float)(Direct3D::scrWidth / 2.0f);
    float h = (float)(Direct3D::scrHeight / 2.0f);
    //Offsetx,yは0
    //minZ = 0, maxZ = 1

    XMMATRIX vp =
    {
        w,  0,  0,  0,
        0, -h,  0,  0,
        0,  0,  1,  0,
        w,  h,  0,  1
    };
    //ビューポート
    XMMATRIX invVp =

    //プロジェクション変換
    XMMATRIX invProj =

    //ビュー変換
    XMMATRIX invView =

    XMFLOAT3 mousePosFront =
    mousePosFront.z = 0.0f;
    XMFLOAT3 mousePosBack =
    mousePosBack.z = 1.0f;


    //① mousePosFrontをベクトルに変換
    //② ①にinvVP、invPrj、invViewをかける
    //③ mousePosBackをベクトルに変換
    //④ ③にinvVP、invPrj、invViewをかける
    //⑤ ②から④に向かってレイをうつ(とりあえずモデル番号はhModel_[0])
    //⑥ レイが当たったらブレークポイントで止める
}

//描画
void Stage::Draw()
{
    Transform blockTrans;

    for (int x = 0; x < XSIZE; x++)
    {
        for (int z = 0; z < ZSIZE; z++)
        {
            for (int y = 0; y < table_[x][z].height + 1; y++)
            {
                blockTrans.position_.x = x;
                blockTrans.position_.y = y;
                blockTrans.position_.z = z;

                int type = table_[x][z].type;

                Model::SetTransform(hModel_[type], blockTrans);
                Model::Draw(hModel_[type]);
            } 
        }
    }
}

//開放
void Stage::Release()
{
}

//ダイアログプロシージャ(代理)
BOOL Stage::DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg)
    {
    case WM_INITDIALOG:
        //ラジオボタンの初期値
        SendMessage(GetDlgItem(hDlg, IDC_RADIO_UP), BM_SETCHECK, BST_CHECKED, 0);

        //コンボボックスの初期値
        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0,((LPARAM) "デフォルト"));
        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0,((LPARAM) "石"));
        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0,((LPARAM) "草"));
        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0,((LPARAM) "砂"));
        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0,((LPARAM) "水"));
        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_SETCURSEL, 0, 0);
      

        return TRUE;
    }
    return FALSE;
}