import xml.etree.ElementTree as ET
from typing import List, Dict, Tuple

root_node = ET.parse('./enwiki-20211220-pages-articles-multistream1.xml').getroot()

print(root_node)