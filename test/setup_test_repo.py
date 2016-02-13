from subprocess import call
import sys
import os

if( len( sys.argv ) != 3 ):
    exit(-1)

base       = os.path.abspath( sys.argv[1] )
base_repo  = os.path.abspath( sys.argv[2] )

call( [ 'svnadmin', 'create', base_repo ] )
call( [ 'svn', 'co', "file:///"+os.path.abspath( base_repo ), base ] )

for d in [
    base + '/d1',
    base + '/d1/d1a',
    base + '/d1/d1b',
    base + '/d1/d1b/f1bb',
    base + '/d1/d1c',
    base + '/d1/d1c/a',
    base + '/d1/d1c/b',
    base + '/d1/d1c/c',
    base + '/d1/d1c/d',
    base + '/d2',
    base + '/d2/d2a',
    base + '/d2/d2b',
    base + '/d3',
    base + '/d4',
    base + '/d4/d4a',
    base + '/d4/d4b'
    ]:
    os.mkdir( d )
    call( [ 'svn', 'add', d ] )



for f in [
    base + '/d1/f1.txt',
    base + '/d1/f2.txt',
    base + '/d1/f3.txt',
    base + '/d1/f4.txt',
    base + '/d1/d1a/f1.txt',
    base + '/d1/d1a/f2.txt',
    base + '/d1/d1a/f3.txt',
    base + '/d1/d1b/f1.txt',
    base + '/d1/d1b/f1bb/f1.txt',
    base + '/d1/d1c/a/f1.txt',
    base + '/d1/d1c/a/f2.txt',
    base + '/d1/d1c/b/f1.txt',
    base + '/d1/d1c/c/f1.txt',
    base + '/d1/d1c/d/f1.txt',
    base + '/d2/f1.txt',
    base + '/d2/d2a/f1.txt',
    base + '/d2/d2b/f1.txt',
    base + '/d3/f1.txt',
    base + '/d4/f1.txt',
    base + '/d4/d4a/f1.txt',
    base + '/d4/d4b/f1.txt'
    ]:
    ff = open( f, 'a' )
    ff.write( f )
    ff.close()
    call( [ 'svn', 'add', f ] )

# Commit initial Revision
call( [ 'svn', 'ci', '-m', "initial revision", base ] )


def add_modification( b, text, message ):

   # Add some modifications
   for f in [
       b + '/d1/f1.txt',
       b + '/d1/d1a/f1.txt',
       b + '/d1/d1c/a/f1.txt',
       b + '/d2/d2a/f1.txt',
       b + '/d2/d2b/f1.txt' ]:
       ff = open( f, 'a' )
       ff.write( ","+text )
       ff.close()

   # Commit initial Revision
   call( [ 'svn', 'ci', '-m', message, b ] )



def add_external( target_dir, source, destination, operative, peg ):
    prop=""
    for t in list( zip( source, destination, operative, peg ) ):
        print( t)
        p = t[0]
        if len( t[3] ) > 0:
            p = p + "@"+t[3]
        p = p + " " + t[1]
        if len( t[2] ) > 0:
            p = " -r "+t[2] + " " + p
        if( len(prop) > 0 ):
            prop = prop+"\n"
        print( p)
        prop += p

    print( prop )
    cmd = [ 'svn', 'propset', 'svn:externals', prop, target_dir ]
    print( ' '.join( cmd ) )
    call( cmd )

add_modification( base, "modification-1", "first modification"  )
add_modification( base, "modification-2", "second modification" )
add_modification( base, "modification-3", "third modification"  )
add_modification( base, "modification-4", "fourth modification" )
add_modification( base, "modification-5", "fifth modification"  )


#reads_correct_external_information1
#reads_correct_external_information2
add_external( base+"/d3", ['^/d2/d2a', '^/d2/d2b' ], [ "external_lib1", 'external_lib2' ], ["4", ""], ["", "2"] )

# reads_correct_external_information3
add_external( base+"/d4", ['^/d2/d2a' ], [ "external_lib3" ], [""], [""] )

# reads_correct_external_information4
# reads_correct_external_information5
# reads_correct_external_information6
add_external( base+"/d1", 
        ['^/d2/d2b', '../d2/d2a', "^/d4/d4a/f1.txt" ], 
        [ "d1b/external_lib4", "./external_lib5", "./an_external_file.xyz" ], 
        ["", "3", "1" ], 
        ["", "3", "2" ])




call( ['svn', 'update', base ])
