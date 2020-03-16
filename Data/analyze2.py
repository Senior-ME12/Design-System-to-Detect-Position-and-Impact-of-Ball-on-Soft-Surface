import pandas as pd 
import numpy as np
import seaborn as sns
import os
from scipy import stats
import matplotlib.pyplot as plt

def RawData():
    frames = {}
    directory = r'Data'
    for filename in os.listdir(directory):
        if filename.endswith(".csv"):
            name = filename.split('.')[0]
            filelocation = os.path.join(directory, filename)
            df = pd.read_csv(filelocation, index_col = 'time') 
            frames[name] = df.drop(['interupt'], axis=1)
    return frames

def NormalizedData(raw):
    normal = {}
    for key, value in raw.items():
        normal[key] = {}
        normal[key]['raw'] = value
        normal[key]['normalized'] = normal[key]['raw'].stack().reset_index(-1).iloc[:, ::-1].rename(columns={0: 'raw', 'level_1': 'snsr'})
        #        normal[key]['median'] = normal[key]['normalized'].groupby(['snsr'])['raw'].median().rename_axis('snsr').reset_index().rename(columns={'raw' :'median'})
        #        normal[key]['normalized'] = normal[key]['normalized'].reset_index().merge(normal[key]['median'], how="left").set_index('time')
        #        normal[key]['normalized']['normalized'] = normal[key]['normalized']['raw'] - normal[key]['normalized']['median']
        #        normal[key]['normalized'] = normal[key]['normalized'].drop(['median'], axis=1)
        #        normal[key]['normalized'] = normal[key]['normalized'].reset_index('time').set_index(['time','snsr']).stack().reset_index().set_index('time').rename(columns={0: 'value', 'level_2': 'type'})
        #        
        normal[key]['tmean'] = normal[key]['normalized'].reset_index('time').drop(['time','raw'], axis=1)['snsr'].drop_duplicates()
        df = pd.DataFrame({'A': stats.trim_mean(value, 0.25)})
        normal[key]['tmean'] = pd.concat([normal[key]['tmean'], df.reindex(normal[key]['tmean'].index)], axis=1).rename(columns={'A' :'tmean'})
        normal[key]['normalized'] = normal[key]['normalized'].reset_index().merge(normal[key]['tmean'], how="left").set_index('time')
        normal[key]['normalized']['normalized'] = normal[key]['normalized']['raw'] - normal[key]['normalized']['tmean']
        normal[key]['normalized'] = normal[key]['normalized'].drop(['tmean'], axis=1)
        normal[key]['normalized'] = normal[key]['normalized'].reset_index('time').set_index(['time','snsr']).stack().reset_index().set_index('time').rename(columns={0: 'value', 'level_2': 'type'})
    return  normal

def LinePlot(frame, data , position):
    # data = raw or normalized 
    df = frame[position]['normalized'].reset_index()
    df = df[df['type'] == data]
    sns.set()    
    sns.lineplot(data=df, x='time', y='value', hue='snsr').set_title(data+ ' data at '+ position)
#    df.plot(linewidth=1,title = data+ ' data at '+ position, colormap = 'tab20')
#    df.plot(kind='line',x='time',y='value',columns = 'type', )
    return

def ExteactImpact(frame):
    frame2 = {}
    for key, value in frame.items():
        df1 = frame[key]['normalized']
        df2 = df1[df1['type'] == 'normalized']
        df2 = df2.drop(['type'], axis = 1).pivot(columns='snsr', values='value')
        df2['max'] = df2.max(axis = 1)
        df2['impact'] = np.nan
        df2 = df2[['max','impact']]    
        
        c = 1
        j = 12
        for i in range(len(df2.index)):
            if j == 12:
                if df2.iloc[i]['max'] > 2:
                    df2['impact'].iloc[i-1:i+10] = np.array(c)
                    c += 1
                    j = 0
            else:
                j += 1
        df1 = df1.reset_index()
        df2 = df2.drop(['max'], axis = 1).reset_index()
        df = df1.merge(df2,how = 'left', on = ['time'])
        frame2[key] = df.set_index('time')    
    return frame2


frame1 = NormalizedData(RawData())
plt.subplot(2,1,1)
LinePlot(frame1,'normalized','1_1')
plt.subplot(2,1,2)
LinePlot(frame1,'raw','1_1')
plt.tight_layout()

frame2 = ExteactImpact(frame1)
#sns.set(style="ticks", palette="pastel")
#sns.boxplot(x="snsr", y="value",hue="type", palette=["m", "g"], data=normal['1_1']['normalized']).set_title('normalized by trimmed mean')

#df = frame2['1_1']
#df = df[(df['impact'].notna()) & (df['type'] == 'normalized')].drop(['type'], axis = 1)
#sns.set( palette="pastel")
##sns.lineplot(data=df, x=df.index, y='value', hue='snsr').set_title(data+ ' data at '+ position)
#
#sns.swarmplot(x='impact',y = 'value',hue = 'snsr', data= df, size=4)
#plt.legend(bbox_to_anchor=(1, 1), loc=2, borderaxespad=0)



columns=['snsr_11','snsr_12','snsr_13','snsr_14',
         'snsr_21','snsr_22','snsr_23','snsr_24',
         'snsr_31','snsr_32','snsr_33','snsr_34',
        'snsr_41','snsr_42','snsr_43','snsr_44','middle']
for key, value in frame2.items():
    df = frame2[key]
    ymin = df['value'].min()
    ymax = df['value'].max()
    plt.figure()
    for i in range(16):
        plt.subplot(4,4,i+1)
        df1 = df[(df['impact'].notna()) & (df['type'] == 'normalized') & (df['snsr'] == columns[i])].drop(['type'], axis = 1)
        sns.lineplot(data=df1, x=df1.index, y='value', hue='impact').set_ylim([ymin,ymax])
        plt.xlabel('')
        plt.ylabel('')
        plt.legend().set_visible(False)
    plt.suptitle(f"impact on snsr {key}", fontsize=16)
    plt.subplots_adjust(top=0.945, bottom=0.04, left=0.04, right=0.995, hspace=0.2, wspace=0.2)
    
#df = frame2['1_1']

    
    
    
