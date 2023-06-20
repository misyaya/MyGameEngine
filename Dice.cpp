#include "Dice.h"


//���_���̏���
void Dice::InitVertexData()
{
	// ���_���
	vertices_ =
	{
		//1
		{ XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f),XMVectorSet(0.0f,  0.0f, 0.0f, 0.0f), XMVectorSet(0.0, 0.0, -1.0, 0.0f) },	// �_�C�X�̒��_�i����P�j0
		{ XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f),	XMVectorSet(0.25f, 0.0f, 0.0f, 0.0f), XMVectorSet(0.0, 0.0, -1.0, 0.0f) },  // �_�C�X�̒��_�i�E��P�j1
		{ XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),	XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f), XMVectorSet(0.0, 0.0, -1.0, 0.0f) },	// �_�C�X�̒��_�i�E���P�j2
		{ XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f),XMVectorSet(0.0f,  0.5f, 0.0f, 0.0f), XMVectorSet(0.0, 0.0, -1.0, 0.0f) },   // �_�C�X�̒��_�i�����P�j3		

		//2
		{ XMVectorSet(-1.0f, 1.0f, 2.0f, 0.0f),XMVectorSet(0.25f, 0.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) },   // �_�C�X�̒��_�i����Q�j4
		{ XMVectorSet(1.0f, 1.0f, 2.0f, 0.0f),	XMVectorSet(0.5f, 0.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) },	// �_�C�X�̒��_�i�E��Q�j5
		{ XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f),	XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)},  // �_�C�X�̒��_�i�E���Q�j6
		{ XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f),XMVectorSet(0.25f,0.5f, 0.0f, 0.0f), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) },	// �_�C�X�̒��_�i�����Q�j7

		//3
		{ XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f),	XMVectorSet(0.5f, 0.0f, 0.0f, 0.0f), XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f) },   // �_�C�X�̒��_�i����Q�j8
		{ XMVectorSet(1.0f, 1.0f, 2.0f, 0.0f),	XMVectorSet(0.75f, 0.0f, 0.0f, 0.0f),XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f) },	// �_�C�X�̒��_�i�E��Q�j9
		{ XMVectorSet(1.0f, -1.0f, 2.0f, 0.0f),XMVectorSet(0.75f, 0.5f, 0.0f, 0.0f), XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f) },   // �_�C�X�̒��_�i�E���R�j10
		{ XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),	XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f), XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f) },	// �_�C�X�̒��_�i�����R�j11

		//4
		{ XMVectorSet(-1.0f, 1.0f, 2.0f, 0.0f),XMVectorSet(0.75f, 0.0f, 0.0f, 0.0f), XMVectorSet(-1.0f, 1.0f, 2.0f, 0.0f) },// �_�C�X�̒��_�i����S�j12
		{ XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f),XMVectorSet(1.0f,0.0f, 0.0f, 0.0f), XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f) },	// �_�C�X�̒��_�i�E��S�j13
		{ XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f),XMVectorSet(1.0f,  0.5f, 0.0f, 0.0f), XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f) },   // �_�C�X�̒��_�i�E���S�j14
		{ XMVectorSet(-1.0f, -1.0f, 2.0f, 0.0f),XMVectorSet(0.75f,  0.5f, 0.0f, 0.0f), XMVectorSet(-1.0f, -1.0f, 2.0f, 0.0f) },   // �_�C�X�̒��_�i�����S�j15

		//5
		{ XMVectorSet(1.0f, -1.0f, 2.0f, 0.0f),XMVectorSet(0.0f, 0.5f, 0.0f, 0.0f), XMVectorSet(1.0f, -1.0f, 2.0f, 0.0f) },   // �_�C�X�̒��_�i����T�j16
		{ XMVectorSet(-1.0f, -1.0f, 2.0f, 0.0f),XMVectorSet(0.25f,  0.5f, 0.0f, 0.0f), XMVectorSet(-1.0f, -1.0f, 2.0f, 0.0f) },   // �_�C�X�̒��_�i�E��T�j17
		{ XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f),XMVectorSet(0.25f,  1.0f, 0.0f, 0.0f), XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f) },   // �_�C�X�̒��_�i�E���T�j18
		{ XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),	XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f) },	// �_�C�X�̒��_�i�����T�j19

		//6
		{ XMVectorSet(1.0f, 1.0f, 2.0f, 0.0f),	XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f), XMVectorSet(1.0f, 1.0f, 2.0f, 0.0f) },	// �_�C�X�̒��_�i����U�j20
		{ XMVectorSet(-1.0f, 1.0f, 2.0f, 0.0f),XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f), XMVectorSet(-1.0f, 1.0f, 2.0f, 0.0f) },   // �_�C�X�̒��_�i�E��U�j21
		{ XMVectorSet(-1.0f, -1.0f, 2.0f, 0.0f),XMVectorSet(0.5f,  1.0f, 0.0f, 0.0f), XMVectorSet(-1.0f, -1.0f, 2.0f, 0.0f) },   // �_�C�X�̒��_�i�E���U�j22
		{ XMVectorSet(1.0f, -1.0f, 2.0f, 0.0f),	XMVectorSet(0.25f, 1.0f, 0.0f, 0.0f), XMVectorSet(1.0f, -1.0f, 2.0f, 0.0f) },	// �_�C�X�̒��_�i�����U�j23


	};
	
	//���_�̐�
	vertexNum_ = vertices_.size();

}


//�C���f�b�N�X��������
void Dice::InitIndexData()
{
	//�C���f�b�N�X���
	index_ = { 0, 2, 3,  0, 1, 2,  7, 4, 5,  7, 5, 6,  8, 9,11,  9,10,11,
					15,12,13, 15,13,14, 18,19,16, 18,16,17, 20,21,22,  20,22,23 }; //2,3,0�ł�3,0,2�ł����v���Ȃ炢��

	//�C���f�b�N�X��
	indexNum_ = index_.size();
}