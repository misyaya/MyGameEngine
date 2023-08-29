#include "Controller.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"



Controller::Controller(GameObject * parent) :GameObject(parent, "Controller")
{

    transform_.position_.x = 7.0f;
    transform_.position_.z = 7.0f;

    transform_.rotate_.x = 45.0f;

}



Controller::~Controller()
{

}



void Controller::Initialize()
{
}



void Controller::Update()
{
    //�E��]
    if (Input::IsKey(DIK_RIGHT))
    {
        transform_.rotate_.y += 1.0f;
    }

    //����]
    if (Input::IsKey(DIK_LEFT))
    {
        transform_.rotate_.y -= 1.0f;
    }
    //transform_.rotate_.y�̒l�ɍ��킹�Ăx����]������s��
    XMMATRIX mRotateY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

    //���]
    if (Input::IsKey(DIK_UP))
    {
        transform_.rotate_.x += 1.0f;
        if (transform_.rotate_.x > 89)
        {
            transform_.rotate_.x = 89;
        }
       
    }

    //����]
    if (Input::IsKey(DIK_DOWN))
    {
        transform_.rotate_.x -= 1.0f;
        if (transform_.rotate_.x < 0)
        {
            transform_.rotate_.x = 0;
        }
    
    }

    //transform_.rotate_.x�̒l�ɍ��킹�Ăw����]������s��
    XMMATRIX mRotateX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));

   
    //���ݒn���x�N�g���^�ɕϊ�
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
   
    //�O��ړ�
    XMVECTOR frontMove = XMVectorSet(0, 0, 0.1f, 0);             //��������XMVECTOR�\���̂�p�ӂ�
    frontMove = XMVector3TransformCoord(frontMove, mRotateY);    //�ړ��x�N�g����]
    if (Input::IsKey(DIK_W))
    {
        //�ړ�
        vPos += frontMove;
    }
    if (Input::IsKey(DIK_S))
    {
        //�ړ�
        vPos -= frontMove;
    }


    //���E�ړ�
    XMVECTOR rightMove = XMVectorSet(0.1f, 0, 0, 0);             //�E������XMVECTOR�\���̂�p�ӂ�
    rightMove = XMVector3TransformCoord(rightMove, mRotateY);    //�ړ��x�N�g����]
    if (Input::IsKey(DIK_D))
    {
        //�ړ�
        vPos += rightMove;
    }
    if (Input::IsKey(DIK_A))
    {
        //�ړ�
        vPos -= rightMove;
    }
    XMStoreFloat3(&transform_.position_, vPos);

   
 
    //�J����
    XMVECTOR vCam = XMVectorSet(0, 0, -10, 0);  //���B��_�p��
    vCam = XMVector3TransformCoord(vCam, mRotateX * mRotateY);//���B��_��]
    Camera::SetPosition(vPos + vCam);
    Camera::SetTarget(transform_.position_); //�J�����̌���ʒu�͂��̃I�u�W�F�N�g�̈ʒu

}



void Controller::Draw()
{

}



void Controller::Release()
{

}
