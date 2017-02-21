# Garrett Scholtes
# Enable / disable virtual address space randomization 
#
# WARNNG: this script overwrites /proc/sys/kernel/randomize_va_space  
# The default value is 2, but some systems may be configured with 1

if [ $1 = "off" ]; then
	echo 0 | sudo tee /proc/sys/kernel/randomize_va_space;
	echo "ASLR disabled!";
elif [ $1 = "on" ]; then
	echo 2 | sudo tee /proc/sys/kernel/randomize_va_space;
	echo "ASLR enabled";
fi