#include "Stage.h"
#include "Engine/Model.h"

//�R���X�g���N�^
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
            table_[x][z] = -1;
        }
    }
}

//�f�X�g���N�^
Stage::~Stage()
{
}

//������
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
        //���f���f�[�^�̃��[�h
        hModel_[i] = Model::Load(fname_base + modelname[i]);
       assert(hModel_[i] >= 0);
    }
  
    //table�Ƀu���b�N�̃^�C�v���Z�b�g���Ă�낤�I

    for (int z = 0; z < ZSIZE; z++)
    {
        for (int x = 0; x < XSIZE; x++)
        {
            table_[x][z] = x % 5;
        }
    }
}

//�X�V
void Stage::Update()
{
}

//�`��
void Stage::Draw()
{
    Transform blockTrans;

    for (int x = 0; x < 15; x++)
    {
        for (int z = 0; z < 15; z++)
        {
            blockTrans.position_.x = x;
            blockTrans.position_.z = z;

            Model::SetTransform(hModel_[type], blockTrans);
            Model::Draw((x + z) % 5);

        }
    }
}

//�J��
void Stage::Release()
{
}