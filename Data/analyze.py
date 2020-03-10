import pandas as pd 
import numpy as np
import matplotlib.pyplot as plt
import os

frames = {}
directory = r'data'
for filename in os.listdir(directory):
    if filename.endswith(".csv"):
        name = filename.split('.')[0]
        filelocation = os.path.join(directory, filename)
        df = pd.read_csv(filelocation, index_col = 'time') 
        df.diff()[1:].drop(['interupt'], axis=1).plot(linewidth=1, 
                                                       title = "Diff1 "+name, 
                                                       colormap = 'tab20')
        plt.legend(loc = 'lower left')
        frames[name] = {}
        frames[name]['rawdata'] = df
        df_diff = df.diff()[1:].drop(['interupt'], axis=1)
        df_diff['max'] = df_diff.max(axis =1) 
        frames[name]['diff'] = df_diff
        
        frames[name]['impact'] = {}
        
        count = 1
        j = 12
        for i in range(len(df_diff.index)):
            if j == 12:
                if df_diff.iloc[i]['max'] > 5:
                    impact_data = df_diff.iloc[i:i+15]
                    frames[name]['impact'][f'impact{count}'] = {}
                    frames[name]['impact'][f'impact{count}']['plot'] = impact_data
#                    frames[name]['impact'][f'impact{count}']['area'] = pd.DataFrame(columns=['snsr_11','snsr_12','snsr_13','snsr_14',
#                                                                                              'snsr_21','snsr_22','snsr_23','snsr_24',
#                                                                                              'snsr_31','snsr_32','snsr_33','snsr_34',
#                                                                                              'snsr_41','snsr_42','snsr_43','snsr_44'])
                    area_dict = {}
                    area_abs_dict = {}
                    for colname, j in impact_data.iteritems(): 
                        if colname != "time" and colname != 'max':
                            impact_data = j
                            snsr_area = np.array(j).transpose()
                            snsr_area_abs = np.array(j.abs()).transpose()
                            area = np.trapz(snsr_area)
                            area_dict[colname] = area
                            area_abs = np.trapz(snsr_area_abs)
                            area_abs_dict[colname] = area_abs
                    frames[name]['impact'][f'impact{count}']['area'] = area_dict
                    frames[name]['impact'][f'impact{count}']['area_abs'] = area_abs_dict
                    
                    count +=1
                    j = 0
            else:
                j += 1
    else:
        continue