import React from 'react'
import Image from 'next/image'

import setting from '../setting'
import { Alert } from 'react-bootstrap'

export default function Home (): React.JSX.Element {
  return (
    <>
      <div id='Index' className='d-flex flex-column align-items-center'>
        <h1>{setting.title}</h1>
        <Image id='Logo' className='mt-3 border rounded-circle' width={100} height={100} src='/tako.png' alt='Logo' />
        <Alert variant='info' className='mt-5'>
          <Alert.Heading>フラクタル図形とは？</Alert.Heading>
          <hr />
          <p>
            フラクタル図形とは、自己相似的な構造を持つ図形のことで、図形の一部を拡大すると、元の図形と同じ形状の図形が現れる特徴があります。
            <br /><br />
            「再帰」という数学的な概念を用いて、コンピュータで描画することができます。
            <br /><br />
            このサイトでは、C++(libpng)を用いて生成したフラクタル図形を、Next.js(TypeScript)を用いて表示しています。
          </p>
        </Alert>
      </div>
    </>
  )
}
