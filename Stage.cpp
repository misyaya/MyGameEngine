#include "Stage.h"
#include "Engine/Model.h"
#include "resource.h"
#include "Engine/Direct3D.cpp"


void Stage::SetBlockType(int _x, int _z, BLOCKTYPE _type)
{ 
    //�G���[�`�F�b�N�@�͈͓��̒l���ǂ��������ق�������
    table_[_x][_z].type = _type;
}

void Stage::SetBlockHeight(int _x, int _z, int _height)
{
    //�G���[�`�F�b�N�@�͈͓��̒l���ǂ��������ق�������
    table_[_x][_z].height = _height;
}

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
            SetBlockType(x, z, DEFAULT);
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
    for (int x = 0; x < ZSIZE; x++)
    {
        for (int z = 0; z < XSIZE; z++)
        {
            SetBlockType(x, z,( BLOCKTYPE)(z%5));
            SetBlockHeight(x, z, x % 5);
        }
    }
}

//�X�V
void Stage::Update()
{
    float w = (float)(Direct3D::scrWidth / 2.0f);
    float h = (float)(Direct3D::scrHeight / 2.0f);
    //Offsetx,y��0
    //minZ = 0, maxZ = 1

    XMMATRIX vp =
    {
        w,  0,  0,  0,
        0, -h,  0,  0,
        0,  0,  1,  0,
        w,  h,  0,  1
    };
    //�r���[�|�[�g
    XMMATRIX invVp =

    //�v���W�F�N�V�����ϊ�
    XMMATRIX invProj =

    //�r���[�ϊ�
    XMMATRIX invView =

    XMFLOAT3 mousePosFront =
    mousePosFront.z = 0.0f;
    XMFLOAT3 mousePosBack =
    mousePosBack.z = 1.0f;


    //�@ mousePosFront���x�N�g���ɕϊ�
    //�A �@��invVP�AinvPrj�AinvView��������
    //�B mousePosBack���x�N�g���ɕϊ�
    //�C �B��invVP�AinvPrj�AinvView��������
    //�D �A����C�Ɍ������ă��C������(�Ƃ肠�������f���ԍ���hModel_[0])
    //�E ���C������������u���[�N�|�C���g�Ŏ~�߂�
}

//�`��
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

//�J��
void Stage::Release()
{
}

//�_�C�A���O�v���V�[�W��(�㗝)
BOOL Stage::DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg)
    {
    case WM_INITDIALOG:
        //���W�I�{�^���̏����l
        SendMessage(GetDlgItem(hDlg, IDC_RADIO_UP), BM_SETCHECK, BST_CHECKED, 0);

        //�R���{�{�b�N�X�̏����l
        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0,((LPARAM) "�f�t�H���g"));
        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0,((LPARAM) "��"));
        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0,((LPARAM) "��"));
        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0,((LPARAM) "��"));
        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0,((LPARAM) "��"));
        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_SETCURSEL, 0, 0);
      

        return TRUE;
    }
    return FALSE;
}