import pandas as pd
from datetime import datetime
import csv
import matplotlib.pyplot as plt
import matplotlib.dates as mdates


df = pd.read_csv('30cm_center.csv')
df.head()

df.plot()
plt.show()
# Plot data in the notebook
#plotly.offline.plot(fig, filename='simple-plot-from-csv')


