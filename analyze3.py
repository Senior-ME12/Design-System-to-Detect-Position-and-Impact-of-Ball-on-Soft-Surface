import pandas as pd 
import numpy as np
import seaborn as sns
import os
from scipy import stats
import matplotlib.pyplot as plt
#from  matplotlib.ticker import FuncFormatter
FOLDER = 'Fifth_test'
FILE = 'middel-5.csv' # file name '1-1.csv' or 'all'
IMPACT = 'all' # impact number 'all' or list ex. [1,2,3,5]
PLOT = True
LINE = False
BAR = True

def RawData(folder,file):
    fileloc = folder+'/'+file
    df = pd.read_csv(fileloc, index_col = 'time')
    df = df.drop(['interupt'], axis=1).dropna()
    return df

def NormalData(raw, plot = True):
    df = raw.sub(stats.trim_mean(raw, 0.25), axis='columns')
    if plot == True:
       plt.figure()
       PlotRN(raw,df) 
    return df

def PlotRN(raw,normal):
    sns.set_style("whitegrid")
    plt.subplot(2,1,1)
    raw.plot(title = 'Raw Data', colormap = 'tab20',ax=plt.gca())
    plt.ylabel(f'acceleration (m/s\N{SUPERSCRIPT TWO})')
    plt.xlabel('time (ms)')
    plt.legend(loc='center left', bbox_to_anchor=(1, 0))
    
    plt.subplot(2,1,2)
    normal.plot(title = 'Normalized Data', colormap = 'tab20',ax=plt.gca())
    plt.ylabel(f'acceleration (m/s\N{SUPERSCRIPT TWO})')
    plt.xlabel('time (ms)')
    plt.legend().set_visible(False)
    
    plt.subplots_adjust(top=0.905, bottom=0.11, left=0.11, right=0.905, hspace=0.380, wspace=0.23)
    return

def FindImpact(normal):
    normal.loc[:, 'max'] = abs(normal).max(axis = 1)
    normal.loc[:, 'impact'] = np.nan
    normal = normal.reset_index()
    c,k = 15,0
    for index, row in normal.iterrows():
        if (row['max'] > 50.0) and (c > 20):
            k += 1
            c = 0
            normal.loc[index-5:index+30, 'impact'] = k
        else:
            c += 1
    return normal.dropna().drop(['max'],axis=1).set_index(['time','impact']), k

def FilterImpact(normalwithimpact,impactlist,N,line = True, bar = True):
    if ((type(impactlist) == list) and (all(isinstance(x, int) for x in impactlist)) and max(impactlist)<= N)  or (impactlist == 'all'):
        if impactlist != 'all':
            impactlist = [x for x in impactlist if x <= N]
            df = normalwithimpact.query('impact in @impactlist')

        else:
            df = normalwithimpact
            impactlist = list(range(1,N+1))
        columns=['snsr_11','snsr_12','snsr_13','snsr_14',
                     'snsr_21','snsr_22','snsr_23','snsr_24',
                     'snsr_31','snsr_32','snsr_33','snsr_34',
                     'snsr_41','snsr_42','snsr_43','snsr_44']     
        #plot impact
        if line == True:
            plt.figure()
            df1 = df.stack().reset_index().rename({'level_2': 'snsr_name',0:'snsr_value'}, axis=1)
            
            sns.set_style("whitegrid")
            
            ymin, ymax = min(df1.snsr_value), max(df1.snsr_value)
            for i in range(16):
                plt.subplot(4,4,i+1)
                df2 = df1[df1['snsr_name'] == columns[i]]
                sns.lineplot(data=df2, x='time', y='snsr_value', hue='impact').set_ylim([ymin,ymax])
                plt.xlabel('')
                plt.ylabel('')
                plt.xticks(fontsize=10)
                plt.yticks(fontsize=10)
                plt.legend().set_visible(False)
            plt.suptitle(f"Acceleration (m/s\N{SUPERSCRIPT TWO}) - Time (ms) on sensor {FILE.split('.')[0]} ({FOLDER})", fontsize=16)
            plt.subplots_adjust(top=0.920, bottom=0.04, left=0.04, right=0.995, hspace=0.2, wspace=0.2)
            
        #plot area
        dfarea = pd.DataFrame(columns=['impact','snsr_11','snsr_12','snsr_13','snsr_14',
                                           'snsr_21','snsr_22','snsr_23','snsr_24',
                                           'snsr_31','snsr_32','snsr_33','snsr_34',
                                           'snsr_41','snsr_42','snsr_43','snsr_44'])
        for j in impactlist:
            df3 = df.query('impact == @j')
            area = [j] + list(np.trapz(df3.abs(), axis=0))  #df3.abs()
            area = pd.Series(area, index = dfarea.columns)
            dfarea = dfarea.append(area, ignore_index=True)
        dfarea = dfarea.set_index('impact').stack().reset_index().rename({'level_1': 'snsr_name',0:'snsr_area'}, axis=1)
#            dfarea.impact = dfarea.impact.astype(int).astype(str)
        dfareasum = dfarea[['impact','snsr_area']].groupby('impact').agg({'snsr_area':np.sum})
        if bar == True:
            
            plt.figure()
            sns.set_style("whitegrid")
            ymin, ymax = min(dfarea.snsr_area), max(dfarea.snsr_area)
            for i in range(16):
                plt.subplot(4,4,i+1)
                df4 = dfarea[dfarea['snsr_name'] == columns[i]]
                sns.barplot(data=df4, x=[int(x) for x in impactlist], y='snsr_area').set_ylim([0,ymax])
                plt.xlabel('')
                plt.ylabel('')
            
    #            plt.legend().set_visible(False)
    #            plt.yaxis.set_major_locator(MaxNLocator(integer=True))
    #            plt.gca().xaxis.set_major_formatter(FuncFormatter(lambda x, _: int(x)))
            plt.suptitle(f"Area (mm/s) on sensor {FILE.split('.')[0]} ({FOLDER})", fontsize=16)
            plt.subplots_adjust(top=0.945, bottom=0.04, left=0.04, right=0.995, hspace=0.2, wspace=0.2)
            
    #       
#            plt.figure()
#            sns.set_style("whitegrid")
#            sns.barplot(data=dfareasum, x=[int(x) for x in dfareasum.index], y='snsr_area')
#            plt.xlabel('')
#            plt.ylabel('')
#    
#            plt.suptitle(f"Sum Area (mm/s) on sensor {FILE.split('.')[0]} ({FOLDER})", fontsize=16)
#            plt.subplots_adjust(top=0.945, bottom=0.04, left=0.04, right=0.995, hspace=0.2, wspace=0.2)

    else :
        df = print('Argument error')  
        dfarea = print('Argument error')  
        dfareasum = print('Argument error')  
    return df, dfarea, dfareasum

def Answer(areadf,n):
    df = pd.DataFrame(columns=['impact','column','row'])
    for x in range(n):
        df1 = areadf[areadf['impact'] == x+1]['snsr_area']
        df2 = np.reshape(df1.to_numpy(), (4, 4))
        column = np.argmax(np.sum(df2, axis=0))+1
        row = np.argmax(np.sum(df2, axis=1))+1
        df = df.append({'impact': x+1, 'column':column, 'row' : row}, ignore_index=True)
    return df

if FILE == 'all':
    frames = {}
    directory = FOLDER
    for filename in os.listdir(directory):  # or filesname in ['1-1.csv','1-2.csv','1-3.csv','1-4.csv','2-1.csv','2-2.csv', '2-3.csv', '2-4.csv', '3-1.csv', '3-2.csv', '3-3.csv', '3-4.csv', '4-1.csv', '4-2.csv', '4-4.csv',]
        if filename.endswith(".csv"):
            FILE = filename
            name = filename.split('.')[0]
#            INPUT1 = name
            frames[name] = {}
            df1 = RawData(FOLDER,FILE)
            df2 = NormalData(df1,plot = PLOT)           
            df3,n = FindImpact(df2)
            df4,area,areasum = FilterImpact(df3, IMPACT, n, line = LINE, bar = BAR) 
            answer = Answer(area,n)
            frames[name]['raw'] = df1
            frames[name]['normalized'] = df2
            frames[name]['impact'] = df3
            frames[name]['area'] = area
            frames[name]['areasum'] = areasum
            frames[name]['answer'] = answer
    locals()[FOLDER] = frames
    del area,df1,df2,df3,df4,directory,filename,n,name,frames,areasum,answer
    
else :
    df1 = RawData(FOLDER,FILE)
    df2 = NormalData(df1,plot = PLOT)           
    df3,n = FindImpact(df2)
    df4,area,areasum = FilterImpact(df3, IMPACT, n, line = LINE, bar = BAR)
    answer = Answer(area,n)
