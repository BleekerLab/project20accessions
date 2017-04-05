# genericAlias.sql was originally generated by the autoSql program, which also 
# generated genericAlias.c and genericAlias.h.  This creates the database representation of
# an object which can be loaded and saved from RAM in a fairly 
# automatic way.

#Generic 2-column name-alias association.
CREATE TABLE genericAlias (
    name varchar(255) not null,	# Item name (shared with a track table).
    alias varchar(255) not null,	# Another commonly used name for this item.
              #Indices
    INDEX(name(20))
);
