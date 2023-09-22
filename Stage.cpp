#include "Stage.h"

#include "resource.h"
#include "Engine/Direct3D.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/Model.h"

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
            SetBlockType(x, z,( BLOCKTYPE)(0));
            SetBlockHeight(x, z, 0);
        }
    }
}

//�X�V
void Stage::Update()
{
    if (!Input::IsMouseButtonDown(0))
    {
        return;
    }

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
    XMMATRIX invVP = XMMatrixInverse(nullptr, vp);

    //�v���W�F�N�V�����ϊ�
    XMMATRIX invProj = XMMatrixInverse(nullptr, Camera::GetProjectionMatrix());

    //�r���[�ϊ�
    XMMATRIX invView = XMMatrixInverse(nullptr, Camera::GetViewMatrix());

    XMFLOAT3 mousePosFront = Input::GetMousePosition();
    mousePosFront.z = 0.0f;
    XMFLOAT3 mousePosBack = Input::GetMousePosition();
    mousePosBack.z = 1.0f;


    //�@ mousePosFront���x�N�g���ɕϊ�
    XMVECTOR vMouseFront = XMLoadFloat3(&mousePosFront);
    //�A �@��invVP�AinvPrj�AinvView��������
    vMouseFront = XMVector3TransformCoord(vMouseFront, invVP * invProj * invView);
    //�B mousePosBack���x�N�g���ɕϊ�
    XMVECTOR vMouseBack = XMLoadFloat3(&mousePosBack);
    //�C �B��invVP�AinvPrj�AinvView��������
    vMouseBack = XMVector3TransformCoord(vMouseBack, invVP * invProj * invView);
 
    for (int x = 0; x < 15; x++)
    {
        for (int z = 0; z < 15; z++)
        {
            for (int y = 0; y < table_[x][z].height + 1; y++)
            {
                //�D �A����C�Ɍ������ă��C������(�Ƃ肠�������f���ԍ���hModel_[0])
                RayCastData data;
                XMStoreFloat4(&data.start, vMouseFront );
                XMStoreFloat4(&data.dir, vMouseBack - vMouseFront);

                Transform trans;
                trans.position_.x = x;
                trans.position_.y = y;
                trans.position_.z = z;

                Model::SetTransform(hModel_[0], trans);

                Model::RayCast(hModel_[0], data);

                //�E ���C������������u���[�N�|�C���g�Ŏ~�߂�
                if (data.hit && mode_ == 0)
                {
                    table_[x][z].height++;

                    break;
                }
                else if(data.hit && mode_ == 1 && table_[x][z].height != 0)
                {
                    table_[x][z].height--;
                    break;
                }
            }

        }
    }
    
    
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

    case WM_COMMAND:
        if (HIWORD(wp) == BN_CLICKED)
        {
            //�����������擾
            int radioButtonId = LOWORD(wp);

            switch (radioButtonId)
            {
            case IDC_RADIO_UP:
                mode_ = 0;  //UP�ɐ؂�ւ�
                break;

            case IDC_RADIO_DOWN:
                mode_ = 1; //DOWN�ɐ؂�ւ�
                break;

            case IDC_RADIO_CHANGE:
                mode_ = 2; //CHANGE�ɐ؂�ւ�
                break;


            default:
                break;
            }

            return TRUE;
        }

    }
    return FALSE;
}