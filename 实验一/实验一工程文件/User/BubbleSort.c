void BubbleSort(int *data, int size)					
//���ܽ�Ϊð������ĺ���
//����Ϊ���������ֱ�Ϊָ������������С
{
	int i, j, tmp;
	for(i = 0; i < size - 1;i++){
		for(j = 0;j < size - i - 1; j++){
			if(data[j] > data[j+1]){	
				tmp = data[j];
				data[j] = data[j+1];
				data[j+1] = tmp;
				/*�Ƚ�������Ԫ�ص�ֵ����ǰ�ߣ����ߣ�
				��ǰ���߽���λ�ã��ﵽ�������󡰸�����
				��С����ǰ��������Ŀ��*/
			}
		}
	}
}
void BubbleSortNote(int *data, int *pos, int size)
//ð������ͬʱ��¼�����������ԭ����λ�õĺ���
{
	int i, j, tmp;
	for(i = 0; i < size - 1;i++){
		for(j = 0;j < size - i - 1; j++){
			if(data[j] > data[j+1]){	
				tmp = data[j];
				data[j] = data[j+1];
				data[j+1] = tmp;
				//ð������
				tmp = pos[j];
				pos[j] = pos[j+1];
				pos[j+1] = tmp;
				/*ԭ����ͳ�ʼλ������һһ��Ӧ��
				����ʹ��ͬ��ֵ��ԭʼλ��Ҳ��ͬ��
				����data[3] = data[9];
				��ԭʼpos[3] = 3, pos[9] = 9��
				�������ֲ�ͬλ�õ���ͬ��
				��main���������ɳ�ʼλ������pos��
				�����ͬʱ��λ���������ͬ����Ԫ�ؽ�����
				���˳������������һ�£�
				�Ӷ��õ�������ɺ��Ӧ����ԭ�����е�λ��*/
			}
		}
	}
}
