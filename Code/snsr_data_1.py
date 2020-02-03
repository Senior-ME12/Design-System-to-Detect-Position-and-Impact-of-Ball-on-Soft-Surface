### 1 change filelocation
### 2 change csfile name
### save the plot

import pandas as pd 
import numpy as np
import matplotlib.pyplot as plt
import csv

filelocation = 'E:/Work/Senior Project/Data/Second_test/1_1.csv'
csvfile = '1_1-summary.csv'
rawdata = pd.read_csv(filelocation) 
data = pd.read_csv(filelocation, header=0, index_col=0, squeeze=True) 
snsr = data[['snsr_11','snsr_12','snsr_21','snsr_22','interupt']]
snsr.drop(['interupt'], axis=1).plot(linewidth=0.5, title = "Data")
snsr = snsr.iloc[2:]

k = 0
j = 0
for i in range(len(snsr.index)) :
    if snsr.interupt.iloc[i] == 1 and k == 0:
        k = 18
        j = j+1
        snsr.interupt.iloc[i],snsr.interupt.iloc[i-1],snsr.interupt.iloc[i-2] = j,j,j
    elif k < 20 and k > 0:
        snsr.interupt.iloc[i] = j
    else:
        snsr.interupt.iloc[i] = 0
    if k>0:
        k = k-1

impact_name = []
for i in range(1,j+1): 
    impact_name.append(f'Impact {i}')
d = {}
d = {name: snsr.loc[snsr.interupt == impact_name.index(name)+1] for name in impact_name}
predict = []
accuracy = 0

with open(csvfile, 'w', newline ='') as f:
    writer = csv.writer(f)
    writer.writerow(['impact_no','snsr_no','area','area_abs','first','second','first_abs','second_abs','first_diff','second_diff','first_diff_abs','second_diff_abs','ratio'])
for name in impact_name:
    df = d[name].drop(['interupt'], axis=1)
    df_diff = df.diff().fillna(0)
    predict.append(df_diff.iloc[1].idxmin())
    fig, axs = plt.subplots(2)
    fig.suptitle(name)
    axs[0].plot(df)
    axs[0].set_title('sensor data')
    axs[1].plot(df_diff)
    axs[1].set_title('diff')
    plt.legend(df.columns, loc='upper center', bbox_to_anchor=(0.5, -0.1), ncol=4)
    figManager = plt.get_current_fig_manager()
    figManager.window.showMaximized()
    fig.savefig('1_1 ' + str(name) + '.png')
    
    for colname, j in df.iteritems(): 

        snsr_a = np.array(j).transpose()
        area = np.trapz(snsr_a)
        
        snsr_abs = np.array(j.abs()).transpose()
        area_abs = np.trapz(snsr_abs)
        
        first = np.trapz(snsr_a[:10])
        second = np.trapz(snsr_a[10:])
        
        first_abs = np.trapz(snsr_abs[:10])
        second_abs = np.trapz(snsr_abs[10:])
        
        first_diff = np.trapz(np.array(j.diff().fillna(0)[:10]).transpose())
        second_diff = np.trapz(np.array(j.diff().fillna(0)[10:]).transpose())
        
        first_diff_abs = np.trapz(np.array(j.diff().fillna(0).abs()[:10]).transpose())
        second_diff_abs = np.trapz(np.array(j.diff().fillna(0).abs()[10:]).transpose())

        with open(csvfile, 'a', newline ='') as f:
            writer = csv.writer(f)
            writer.writerow([name, colname, area, area_abs, first, second, first_abs, second_abs, first_diff, second_diff, first_diff_abs, second_diff_abs, second_diff_abs/first_diff_abs])
for i in range(len(predict)):
    if predict[i] == 'snsr_11':
        accuracy += 1

print('Accuracy of closest sensor prediction = ' + str((accuracy/len(predict)) * 100) + '%')
