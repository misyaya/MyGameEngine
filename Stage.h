#pragma once
#include "Engine/GameObject.h"
#include "windows.h"

namespace
{
    const int MODEL_NUM{ 5 };
    //��const int MODEL_NUM = 5;�@�Ɠ���
    const int XSIZE{ 15 };
    const int ZSIZE{ 15 };
    enum BLOCKTYPE
    {
        DEFAULT,BRICK,GRASS,SAND,WATER
    };

   
};


//���������Ǘ�����N���X
class Stage : public GameObject
{
    int hModel_[MODEL_NUM];    //���f���ԍ�
   // int table_[XSIZE][ZSIZE];

    struct
    {
        int type;
        int height;
    }table_[XSIZE][ZSIZE];

    struct Cell {
        int type;
        int height;
    };

    int mode_;    //0:�n�ʏグ�� 1:������  2:��ނ�ς���
    int select_; //���

    int blockType_;

    bool flag_ = true;
    
public:
    //�u���b�N�w��
    void SetBlockType(int _x, int _z, BLOCKTYPE _type);

    //�u���b�N����
    void SetBlockHeight(int _x, int _z, int _height);

    //�R���X�g���N�^
    Stage(GameObject* parent);

    //�f�X�g���N�^
    ~Stage();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
    BOOL DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);

    //�Z�[�u
    void Save();

    //���[�h
    void Load();
};