// BiPathTracing01.cpp : �R���\�[�� �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//

#include "stdafx.h"

#include "render.h"


int main(int argc, char* argv[])
{
	edubpt::Camera camera(
		// �o�͉摜�̉𑜓x�i�C���[�W�Z���T�Ƀ}�b�s���O�����j
		640, 480,
		// �C���[�W�Z���T�̒������̈ʒu
		edubpt::Vec(50.0, 40.8, 220.0),
		// �C���[�W�Z���T�̌����Ă������
		normalize(edubpt::Vec(0.0, 0.0, -1.0)),
		// �C���[�W�Z���T�ɑ΂������x�N�g��
		edubpt::Vec(0.0, 1.0, 0.0),
		// �C���[�W�Z���T�̏c���i�����I�傫���j
		30.0,
		// �C���[�W�Z���T�ƃ����Y�̋���
		//30.0,
		42.3,
		//60.0,

		// ���ŋ����i�����Y�ƃI�u�W�F�N�g�v���[���̋����j
		200.0,
		// �����Y���a
		5.0,
		// �Z���T���x�i�ŏI�I�ȏo�͉�f�l�ɑ΂���X�P�[���l�B�����RGB�S�ē����Ƃ���j
		// �K���Ɍ��߂�
		//28.0,
		56.0,
		// �s�N�Z��������̃T���v�����O��
		// �o�����p�X�g���̏ꍇ�A�s�N�Z���������eye�p�X�Elight�p�X�̒ǐՉ񐔂ƂȂ�
		500);

	const int num_threads = 4;

	// ���t�@�����X�p�̃p�X�g���[�V���O�ŉ摜�����i�o�����p�X�g���Ƃ͓Ɨ��j
	//	edubpt::render_by_refernce_pathtracing(camera, num_threads);

	// �J���������璸�_�������ĉ摜����
	//	edubpt::render_by_pathtracing(camera, num_threads);

	// ���������璸�_�������ĉ摜����
	//	edubpt::render_by_lighttracing(camera, num_threads);

	// �o�����p�X�g���ŉ摜����
	edubpt::render_by_bidirectional_pathtracing(camera, num_threads);

	return 0;
}

