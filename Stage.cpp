#include "Stage.h"
#include "Engine/Model.h"

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
    for (int z = 0; z < ZSIZE; z++)
    {
        for (int x = 0; x < XSIZE; x++)
        {
            SetBlockType(x, z,( BLOCKTYPE)(z%5));
            SetBlockHeight(x, z, x % 4);
        }
    }
}

//更新
void Stage::Update()
{
}

//描画
void Stage::Draw()
{
    Transform blockTrans;

    for (int x = 0; x < XSIZE; x++)
    {
        for (int z = 0; z < ZSIZE; z++)
        {
            for (int y = 0; y < table_[x][z].height; y++)
            {
                blockTrans.position_.x = x;
                blockTrans.position_.y = y;
                blockTrans.position_.z = z;

                int type = table_[x][z].type;

                Model::SetTransform(hModel_[type], blockTrans);
                Model::Draw(hModel_[type]);
                SetBlockHeight(x, z, y);
            } 
        }
    }
}

//開放
void Stage::Release()
{
}