#include "Stage.h"
#include "resource.h"
#include "Engine/Direct3D.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/Model.h"
#include <iostream>
#include <Windows.h>
#include <fstream>
#include <sstream>
using std::cout;
using std::cin;
using std::endl;
using std::ofstream;

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
    :GameObject(parent, "Stage"), hModel_{ -1,-1,-1,-1,-1 }
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
            SetBlockType(x, z, (BLOCKTYPE)(0));
            SetBlockHeight(x, z, 0);
        }
    }
}

//更新
void Stage::Update()
{
    if (!Input::IsMouseButtonDown(0))
    {
        return;
    }

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
    XMMATRIX invVP = XMMatrixInverse(nullptr, vp);

    //プロジェクション変換
    XMMATRIX invProj = XMMatrixInverse(nullptr, Camera::GetProjectionMatrix());

    //ビュー変換
    XMMATRIX invView = XMMatrixInverse(nullptr, Camera::GetViewMatrix());

    XMFLOAT3 mousePosFront = Input::GetMousePosition();
    mousePosFront.z = 0.0f;
    XMFLOAT3 mousePosBack = Input::GetMousePosition();
    mousePosBack.z = 1.0f;


    //① mousePosFrontをベクトルに変換
    XMVECTOR vMouseFront = XMLoadFloat3(&mousePosFront);
    //② ①にinvVP、invPrj、invViewをかける
    vMouseFront = XMVector3TransformCoord(vMouseFront, invVP * invProj * invView);
    //③ mousePosBackをベクトルに変換
    XMVECTOR vMouseBack = XMLoadFloat3(&mousePosBack);
    //④ ③にinvVP、invPrj、invViewをかける
    vMouseBack = XMVector3TransformCoord(vMouseBack, invVP * invProj * invView);

    for (int x = 0; x < 15; x++)
    {
        for (int z = 0; z < 15; z++)
        {
            for (int y = 0; y < table_[x][z].height + 1; y++)
            {
                //⑤ ②から④に向かってレイをうつ(とりあえずモデル番号はhModel_[0])
                RayCastData data;
                XMStoreFloat4(&data.start, vMouseFront);
                XMStoreFloat4(&data.dir, vMouseBack - vMouseFront);

                Transform trans;
                trans.position_.x = x;
                trans.position_.y = y;
                trans.position_.z = z;

                Model::SetTransform(hModel_[0], trans);

                Model::RayCast(hModel_[0], data);

                //⑥ レイが当たったらブレークポイントで止める
                if (data.hit && mode_ == 0 && flag_)
                {
                    table_[x][z].height++;
                    table_[x][z].type = blockType_;
                    flag_ = false;
                    break;
                }
                else if (data.hit && mode_ == 1 && table_[x][z].height != 0 && flag_)
                {
                    table_[x][z].height--;
                    flag_ = false;
                    break;
                }
                else if (data.hit && mode_ == 2 && flag_)
                {
                    table_[x][z].type = blockType_;
                    flag_ = false;
                    break;
                }
            }

        }
    }

    flag_ = true;
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
        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, ((LPARAM)"デフォルト"));
        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, ((LPARAM)"石"));
        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, ((LPARAM)"草"));
        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, ((LPARAM)"砂"));
        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, ((LPARAM)"水"));
        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_SETCURSEL, 0, 0);

        return TRUE;

    case WM_COMMAND:
        if (HIWORD(wp) == BN_CLICKED)
        {
            if (LOWORD(wp) == IDC_BUTTON_RESET) 
            {
                for (int x = 0; x < XSIZE; x++)
                {
                    for (int z = 0; z < ZSIZE; z++)
                    {
                        table_[x][z].type = 0;
                        table_[x][z].height = 0;
                    }
                }
                //MessageBox(hDlg, "ボタンがクリックされました", "メッセージ", MB_OK);
                return (INT_PTR)TRUE;
            }

            if (LOWORD(wp) == IDC_BUTTON_UP)
            {
                for (int x = 0; x < XSIZE; x++)
                {
                    for (int z = 0; z < ZSIZE; z++)
                    {
                        table_[x][z].type = blockType_;
                        table_[x][z].height = table_[x][z].height + 1;
                    }
                }
                //MessageBox(hDlg, "ボタンがクリックされました", "メッセージ", MB_OK);
                return (INT_PTR)TRUE;
            }
          
            if (LOWORD(wp) == IDC_BUTTON_DOWN)
            {
                for (int x = 0; x < XSIZE; x++)
                {
                    for (int z = 0; z < ZSIZE; z++)
                    {
                        if (table_[x][z].height > 0 )
                        {
                            table_[x][z].height = table_[x][z].height - 1;
                        }
                        
                    }
                }
                //MessageBox(hDlg, "ボタンがクリックされました", "メッセージ", MB_OK);
                return (INT_PTR)TRUE;
            }

            //何押したか取得
            int radioButtonId = LOWORD(wp);

            switch (radioButtonId)
            {
            case IDC_RADIO_UP:
                mode_ = 0;  //UPに切り替え
                break;

            case IDC_RADIO_DOWN:
                mode_ = 1; //DOWNに切り替え
                break;

            case IDC_RADIO_CHANGE:
                mode_ = 2; //CHANGEに切り替え
                break;


            default:
                break;
            }



            return TRUE;
        }

        if (HIWORD(wp) == CBN_SELCHANGE && LOWORD(wp) == IDC_COMBO2)
        {
            int selectedIndex = SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_GETCURSEL, 0, 0);

            // 選択されたインデックスに基づいてオブジェクトを切り替える
            switch (selectedIndex)
            {
            case 0:
                blockType_ = 0;
                break;
            case 1:
                blockType_ = 1;
  
                break;
            case 2:
                blockType_ = 2;
                break;
            case 3:
                blockType_ = 3;
                break;
            case 4:
                blockType_ = 4;
                break;
            case 5:
                blockType_ = 5;
                break;
            default:
                blockType_ = 0; // デフォルトの値
                break;
            }
        }

    }
    return FALSE;
}


// セーブ
void Stage::Save()
{
    char szFileName[MAX_PATH] = "";

    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(OPENFILENAME));
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.lpstrFilter = TEXT("マップデータ(*.map)\0*.map\0")
        TEXT("すべてのファイル(*.*)\0*.*\0\0");
    ofn.lpstrFile = szFileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_OVERWRITEPROMPT;

    // ファイル名を指定してセーブダイアログを表示
    if (GetSaveFileName(&ofn)) {
        // ファイル名を szFileName から取得
        std::string fileName = szFileName;

        // ファイルをオープン
        std::ofstream file(fileName);
        if (file.is_open()) {
            for (int z = 0; z < ZSIZE; z++) {
                for (int x = 0; x < XSIZE; x++) {
                    file << table_[x][z].type << "," << table_[x][z].height;
                    file << table_[x][z].type << "," << table_[x][z].height;

                    // 最後の要素でない場合、カンマを追加
                    if (x < XSIZE - 1) {
                        file << ",";
                    }
                }
                file << std::endl; // 各行の終わりに改行文字を追加
            }
            file.close();
        }
        else {
            std::cerr << "ファイルを開けませんでした。" << std::endl;
        }
    }
}



void Stage::Load()
{
    char szFileName[MAX_PATH] = "";

    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(OPENFILENAME));
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.lpstrFilter = TEXT("マップデータ(*.map)\0*.map\0")
        TEXT("すべてのファイル(*.*)\0*.*\0\0");
    ofn.lpstrFile = szFileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_FILEMUSTEXIST;

    // ファイルを選択
    if (GetOpenFileName(&ofn)) {
        std::ifstream file(szFileName);
        if (file.is_open()) 
        {
            for (int x = 0; x < XSIZE; ++x)
            {
                for (int z = 0; z < ZSIZE; ++z) 
                {
                    std::string token;
                    if (std::getline(file, token, ',')) 
                    {
                        int value = std::stoi(token);
                        table_[x][z].type = value;
                        if (z % 2 == 1) 
                        {
                            if (std::getline(file, token, ',')) 
                            {
                                table_[x][z].height = std::stoi(token);
                            }
                            x++;
                        }
                    }
                }
            }
            file.close();
        }
        else {
            std::cerr << "ファイルを開けませんでした。" << std::endl;
        }
    }
}

