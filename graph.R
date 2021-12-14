library(ggplot2)

x = c(2, 4, 8, 16, 32)
y = c(0.00210541, 0.00235606, 0.00272901, 0.0039601, 0.00554364)

df <- data.frame(x, y)

theme_set(theme_bw())

ggplot(df, aes(x = x, y = y)) +
  geom_line(color = "firebrick", size = 1) +
  scale_x_continuous(trans = "log", breaks = c(2, 4, 8, 16, 32)) +
  scale_y_continuous(breaks = c(0.002, 0.003, 0.004, 0.005, 0.006)) +
  labs(
    x = "Log N° Processor",
    y = "Computational Time (s)"
  ) +
  theme(axis.text.y = element_text(vjust = 1, angle = 30, size = 10)) +
  theme(axis.text.x = element_text(vjust = 1, angle = 0, size = 10))
  