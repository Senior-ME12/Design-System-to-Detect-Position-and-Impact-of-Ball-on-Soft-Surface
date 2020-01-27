import pandas as pd 
import numpy as np

#for midddle
#rawdata = data = pd.read_csv("Test1/Middle.csv") 
#data = pd.read_csv("Test1/Middle.csv",header=0, index_col=0, squeeze=True) 

rawdata = data = pd.read_csv("Test1/1_1.csv") 
data = pd.read_csv("Test1/1_1.csv",header=0, index_col=0, squeeze=True) 

data.plot(linewidth=0.5, title = "data")

rm_data = data.rolling(window=4).mean()
rm_data.plot(linewidth=0.5, title = "rolling mean data")

data_diff = data.diff()
data_diff.plot(linewidth=0.5, title = "data diff")

rm_diff = data_diff.rolling(window=4).mean()
rm_diff.plot(linewidth=0.5, title = "rolling mean data diff")

data_diff2 = data_diff.diff()
data_diff2.plot(linewidth=0.5)

#for middle 
#timelist = ["95:145", "185:235", "285:335", "375:420", "470:520", "560:610", "655:705", "735:785", "820:870", "910:960","1005:1055","1120:1170"]

timelist = ["305:355", "410:460", "500:550", "600:650", "695:745", "795:845", "890:940", "1000:1050", "1090:1140", "1185:1235"]
for i in timelist:
    print(i)
    timelist_str = i.split(':')
    a = int(timelist_str[0])
    b = int(timelist_str[1])
    impact = data.iloc[a:b]
    for colname, j in impact.iteritems(): 
        if colname != "time":
            snsr = j
            snsr_a = np.array(j).transpose()
            area = np.trapz(snsr_a)
            print(colname,"area",area)
