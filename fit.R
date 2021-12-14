library(tidyverse)
library(ggplot2)
name = "intel benchmarks.xlsx - S-ucx-vader.csv"

csv <- read.csv(name, skip = 2, header = F)

x = csv$V1
y1 = csv$V3
y2 = csv$V4

# LATENCY
df1 <- data.frame(x, y1)
fit_latency <- lm(y1 ~ poly(x, 5, raw=TRUE), data = df1)
plot(df1$x, df1$y1, pch = 19, xlab = 'x', ylab = 'y')
lines(x, predict(fit_latency, data.frame(x = x)), col = 'green')
latency_predict <- predict(fit_latency, data.frame(x = x))

# BANDWIDTH
df2 <- data.frame(x, y2)
fit_bandwitdh <- lm(y2 ~ poly(x, 4, raw=TRUE), data = df2)
plot(df2$x, df2$y2, pch = 19, xlab = 'x', ylab = 'y')
lines(x, predict(fit_bandwitdh, data.frame(x = x)), col = 'green')
bandwidth_predict <- predict(fit_bandwitdh, data.frame(x = x))

csv$V5 = latency_predict
csv$V6 = bandwidth_predict

##################
# IMPROVE HEADER #
##################
csv_header_1 = read.csv(name, nrow = 1, header = F)
names(csv_header_1)<-c("V1","V2","V3","V4","V5","V6")
csv_header_1$V2 = ""
csv_header_1$V3 = ""
csv_header_1$V4 = ""
csv_header_1$V5 = ""
csv_header_1$V6 = ""

csv_nodes = data.frame("ct1p1-tnode007", "ct1p1-tnode008")
names(csv_nodes)<-c("V1","V2")
csv_nodes$V3 = ""
csv_nodes$V4 = ""
csv_nodes$V5 = ""
csv_nodes$V6 = ""

csv_latency_bandwidth = data.frame(latency_predict[1], bandwidth_predict[24])
names(csv_latency_bandwidth)<-c("V1","V2")
csv_latency_bandwidth$V3 = ""
csv_latency_bandwidth$V4 = ""
csv_latency_bandwidth$V5 = ""
csv_latency_bandwidth$V6 = ""

csv_header_2 = data.frame("bytes", "repetitions", "t[usec]", "Mbytes/sec", "t[usec] (computed)", "Mbytes/sec (computed)")
names(csv_header_2)<-c("V1","V2","V3","V4","V5","V6")
###########################
# MERGING ALL THE RESULTS #
###########################

result <- rbind(csv_header_1, csv_nodes, csv_latency_bandwidth, csv_header_2, csv)

write.table(result, paste("./computed/" , name), sep = ",",  col.names = FALSE, row.names = FALSE)

predicted_df <- data.frame(x = x, y = bandwidth_predict)

ggplot(df2, aes(x = x, y = y2)) +
  scale_x_continuous(trans = "log", breaks = x) +
  scale_y_continuous(breaks = y2) +
  geom_line(color='red', data = predicted_df, aes(x=x, y=y))



